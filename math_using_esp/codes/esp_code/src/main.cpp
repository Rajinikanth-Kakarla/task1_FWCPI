#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include"libr.h"
#include <iostream>


AsyncWebServer server(80);

const char* ssid = "Rajinikanth";
const char* password = "Beast@03";

const char* input_parameter00 = "input00";
const char* input_parameter01 = "input01";
const char* input_parameter02 = "input02";
const char* input_parameter10 = "input10";
const char* input_parameter11 = "input11";
const char* input_parameter12 = "input12";
const char* input_parameter20 = "input20";
const char* input_parameter21 = "input21";
const char* input_parameter22 = "input22";
const char* matrix1[3]={input_parameter00,input_parameter01,input_parameter02};
const char* matrix2[3]={input_parameter10,input_parameter11,input_parameter12};
const char* matrix3[3]={input_parameter20,input_parameter21,input_parameter22};

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>COLLINEARITY</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Times New Roman; display: inline-block; text-align: center;}
    h2 {font-size: 2.0rem; color: blue;}
  </style> 
  </head><body>
  <h2>TO FIND IF POINTS ARE COLLINEAR OR NOT</h2> 
  <p>Enter the values of points A,B,C
  <form action="/get">
    Enter the values of Point A: <input type="number" name="input00"><br><input type="number" name="input01"><br><input type="number" name="input02"><br>
    Enter the values of Point B: <input type="number" name="input10"><br><input type="number" name="input11"><br><input type="number" name="input12"><br>
    Enter the values of Point C: <input type="number" name="input20"><br><input type="number" name="input21"><br><input type="number" name="input22"><br>
    <input type="submit" value="Submit">
    

  </form><br>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connecting...");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    /*AngleBisector to find circumcenter and circumradius*/
    
    double A[2] = {1, -1};
    double B[2] = {-4, 6};
    double C[2] = {-3, -5};

    double sides[3];

    tri_sides(A, B, C, sides);
    double a, b, c;
    a = sides[2];
    b = sides[0];
    c = sides[1];

    /* std::cout << "Length of sides of a Triangle" << std::endl;
    std::cout << "a: " << a << "\nb: " << b << "\nc: " << c << std::endl;*/

    double m, n, p;
    p = (a + c - b) / 2;
    m = (a + b - c) / 2;
    n = (b + c - a) / 2;

    /* std::cout << "Insides of a Triangle" << std::endl;
    std::cout << "m: " << m << "\nn: " << n << "\np: " << p << std::endl;*/

    double Dx, Ex, Fx;
    Fx = (m * A[0] + p * B[0]) / (m + p);
    Ex = (p * C[0] + n * A[0]) / (p + n);
    Dx = (n * B[0] + m * C[0]) / (n + m);

    double Dy, Ey, Fy;
    Fy = (m * A[1] + p * B[1]) / (m + p);
    Ey = (p * C[1] + n * A[1]) / (p + n);
    Dy = (n * B[1] + m * C[1]) / (n + m);

    /*std::cout << "Print the point D, E and F" << std::endl;
    std::cout << "Fx: " << Fx << "\nFy: " << Fy << "\nEx: " << Ex << "\nEy: " << Ey << "\nDx: " << Dx << "\nDy: " << Dy << std::endl;*/

    double Ix = (a * C[0] + b * A[0] + c * B[0]) / (a + b + c);
    double Iy = (a * C[1] + b * A[1] + c * B[1]) / (a + b + c);

    /* std::cout << "Print the circumcentre and circumradius of the triangle DEF" << std::endl;
    std::cout << "Ix: " << Ix << "\nIy: " << Iy << std::endl;*/

    if (a + b > c && a + c > b && b + c > a) {
        double r = Radius(a, b, c);
        /*std::cout << "Radius: " << r << std::endl;*/
    }

    /*end*/
    if(1==1)
    {
	request->send(200, "text/html", "Lengths of sides of a triangle a:"+ String(a,2) + "b:"+String(b,2)+"c:"+String(c,2)+"<br>");
	request->send(200, "text/html", "Insides of a triangle m:"+ String(m,2) + "n:"+String(n,2)+"p:"+String(p,2)+"<br>");
	request->send(200, "text/html", "Points D,E,F Dx:"+ String(Dx,2) + "Dy:"+String(Dy,2)+"Ex:"+ String(Ex,2) + "Ey:"+String(Ey,2)+"Fx:"+ String(Fx,2) + "Fy:"+String(Fy,2)+"<br>");
	request->send(200, "text/html", "Circumcenter of a triangle DEF Ix:"+ String(Ix,2) + "Iy:"+String(Iy,2)+"<br>");
	request->send(200, "text/html", "Incenter circle radius r:"+ String(r,2) +"<br>");
	}

  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  
}
