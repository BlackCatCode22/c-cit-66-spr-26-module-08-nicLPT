# tCppModule08spr26
tCppModule08spr26

The Vibe Coding Revolution
Course: CIT-66 C++ Programming (Crow Framework)
Professor: Dennis H. Mohle
1. The Mission

You’ve mastered the fundamentals. You’ve tackled the Zoo Keeper Challenge. Now, you are ready for the professional world of Vibe Coding.

Vibe coding is a modern software development practice where you act as the Architect. Instead of manual memory management and header-file headaches, you guide a high-powered AI assistant (Gemini) to generate and refine complex systems. In 2026, this is how elite C++ engineers move fast without breaking things.

Today, you will build a Global Weather Dashboard. This project will prove to prospective employers that you can handle modern "Modern C++" (C++20/23) and integrate with live web services.

2. Tech Concepts: JSON & Dependencies

In this lab, we use the Crow framework, and we rely on two critical concepts:

JSON (JavaScript Object Notation): The universal data language. Your C++ code will fetch "raw" text data from the government and "parse" it into C++ objects.

Dependencies & Package Managers: In C++, we don't write our own HTTP servers from scratch anymore. We use libraries like Crow (for the web server) and libcurl (for fetching data).

The Manager: You will use vcpkg or Conan. Think of these like an "App Store" for C++ code. Instead of downloading .zip files, you tell the manager what you need, and it handles the complex compilation for you.

3. Step One: Your AI "Coprocessor" (AI Studio)

Go to aistudio.google.com.

Sign in with your Google account.

API Key: On the left sidebar, click "Get API Key." Generate a new key and copy it. (Free for students!)

4. The "Vibe" Workflow: Step by Step
Task A: The Fresno/NY JSON Fetch

The National Weather Service (NWS) is a public service. To get data, you don't need an account, but you must identify your app with a "User-Agent" header.

The Prompt for Gemini:

"I am a C++ student using the Crow framework. Help me write a program that uses libcurl to fetch current weather JSON from the National Weather Service (api.weather.gov) for Fresno, CA and New York, NY. I want to print the raw JSON to the console first. Include a 'User-Agent' header like 'FCC-Student-App'."

Task B: The Human-Readable Web Dashboard

Now, let's turn that data into a real website running on your machine.

The Prompt for Gemini:

"Now, take that C++ weather logic and wrap it in a Crow web server. Create a route for localhost:8080 that returns a professional HTML page with CSS. Use Crow's built-in JSON parser to display the temperature and conditions for Fresno and New York in a clean, high-end dashboard format."

5. The Digital Handshake: Ngrok

Since we are an online class, we cannot use the "neighbor's IP" trick to see each other's work. To make your local C++ server visible to the world, we use a tunnel.

Download Ngrok (ngrok.com).

Run your C++ Crow app (ensure it is listening on port 8080).

In your terminal, type: ngrok http 8080.

The Magic: Ngrok will give you a public URL (e.g., https://fresno-cpp-dev.ngrok-free.app).

Post your URL in the Canvas Discussion board! Click on your classmates' links to see their live C++ dashboards.

6. 🌟 Bonus Opportunity: "London Calling" (+5 Points)

The NWS only covers the US. To go global, you'll need a different "endpoint."

The Task: "Vibe" an integration with the Open-Meteo API (api.open-meteo.com).

The Goal: Add London, UK to your dashboard. This proves you can handle multiple API structures in C++.

Submission Requirements:

Code: Your .cpp source and your CMakeLists.txt (or project file).

The Link: Post your Ngrok URL to the Canvas thread.

The "Vibe" Reflection (Discussion Post): Why is Vibe Coding especially helpful for a complex language like C++?
