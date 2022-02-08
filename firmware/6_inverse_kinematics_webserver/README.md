# Servo Webserver Inverse Kinematics

This code implements inverse kinematics functionality to the existing webserver

## Steps to Follow

- Configure the project
  - `cd firmware/6_inverse_kinematics_webserver`
  - `idf.py menuconfig`
  - `Component config -> MARIO testing -> WiFi Config -> Set SSID -> Set Password`
- Build and Flash the Code
  - `idf.py build`
  - `idf.py -p PORT flash`
- Monitor Logs
  - `idf.py monitor`
- Access website via the ip shown in the `sta ip` part of the terminal. Paste `sta ip` in the browser to access the website
  Note:- If it shows `cmake flash error`. Run the following:
  - `sudo chmod 777 port`
  - `idf.py -p port flash`
