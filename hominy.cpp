#include "crow_all.h"
#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>

#ifdef _WIN32
  #include <winsock2.h>
  #pragma comment(lib, "ws2_32.lib")
#endif

// Struct to hold our final processed data
struct WeatherReport {
    std::string cityName;
    std::string temperature;
    std::string shortForecast;
    std::string detailedForecast;
    bool success = false;
};

// --- libcurl Helper Functions ---
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string fetchWeatherJSON(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "FCC-Student-App");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

WeatherReport getCityWeather(std::string name, std::string pointsUrl) {
    WeatherReport report;
    report.cityName = name;

    // Step 1: Get Forecast URL
    std::string metadataRaw = fetchWeatherJSON(pointsUrl);
    auto metadataJson = crow::json::load(metadataRaw);
    if (!metadataJson || !metadataJson.has("properties")) return report;

    // Convert crow::r_string to std::string explicitly
    std::string forecastUrl = std::string(metadataJson["properties"]["forecast"].s());

    // Step 2: Get Actual Forecast
    std::string forecastRaw = fetchWeatherJSON(forecastUrl);
    auto forecastJson = crow::json::load(forecastRaw);
    if (!forecastJson || !forecastJson.has("properties")) return report;

    auto current = forecastJson["properties"]["periods"][0];

    // FIX: Explicitly cast the unit to std::string
    report.temperature = std::to_string(current["temperature"].i()) + "°" + std::string(current["temperatureUnit"].s());

    // FIX: Cast these as well to prevent similar errors
    report.shortForecast = std::string(current["shortForecast"].s());
    report.detailedForecast = std::string(current["detailedForecast"].s());

    report.success = true;
    return report;
}

int main() {
    curl_global_init(CURL_GLOBAL_ALL);
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        // Fetch data for both cities
        WeatherReport fresno = getCityWeather("Fresno, CA", "https://api.weather.gov/points/36.7468,-119.7726");
        WeatherReport nyc = getCityWeather("New York, NY", "https://api.weather.gov/points/40.7128,-74.0060");

        // Build the HTML with modern CSS
        std::string html = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <title>Weather Dashboard</title>
                <link href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;600&display=swap" rel="stylesheet">
                <style>
                    body { font-family: 'Inter', sans-serif; background: #f0f2f5; margin: 0; padding: 40px; color: #1a1a1a; }
                    .container { max-width: 900px; margin: 0 auto; }
                    header { margin-bottom: 40px; text-align: center; }
                    h1 { font-weight: 600; color: #1e293b; letter-spacing: -1px; }
                    .dashboard { display: grid; grid-template-columns: 1fr 1fr; gap: 25px; }
                    .card { background: white; padding: 30px; border-radius: 16px; box-shadow: 0 4px 6px -1px rgba(0,0,0,0.1); border: 1px solid #e2e8f0; }
                    .city-name { font-size: 14px; text-transform: uppercase; letter-spacing: 1px; color: #64748b; font-weight: 600; margin-bottom: 10px; }
                    .temp { font-size: 48px; font-weight: 600; color: #2563eb; margin: 10px 0; }
                    .condition { font-size: 18px; font-weight: 600; color: #334155; margin-bottom: 15px; }
                    .details { font-size: 14px; line-height: 1.6; color: #475569; }
                    .error { color: #dc2626; font-style: italic; }
                </style>
            </head>
            <body>
                <div class="container">
                    <header>
                        <h1>National Weather Insights</h1>
                    </header>
                    <div class="dashboard">
        )";

        // Fresno Card
        html += "<div class='card'><div class='city-name'>Fresno, CA</div>";
        if (fresno.success) {
            html += "<div class='temp'>" + fresno.temperature + "</div>";
            html += "<div class='condition'>" + fresno.shortForecast + "</div>";
            html += "<div class='details'>" + fresno.detailedForecast + "</div>";
        } else { html += "<div class='error'>Service Unavailable</div>"; }
        html += "</div>";

        // NYC Card
        html += "<div class='card'><div class='city-name'>New York, NY</div>";
        if (nyc.success) {
            html += "<div class='temp'>" + nyc.temperature + "</div>";
            html += "<div class='condition'>" + nyc.shortForecast + "</div>";
            html += "<div class='details'>" + nyc.detailedForecast + "</div>";
        } else { html += "<div class='error'>Service Unavailable</div>"; }
        html += "</div>";

        html += R"(
                    </div>
                </div>
            </body>
            </html>
        )";

        return crow::response(html);
    });

    std::cout << "Dashboard Server running at http://127.0.0.1:8080" << std::endl; // Updated console message
    app.bindaddr("127.0.0.1").port(8080).multithreaded().run();

    curl_global_cleanup();
    return 0;
}