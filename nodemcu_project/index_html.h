#ifndef INDEX_HTML_H
#define INDEX_HTML_H

//Webpage
//handles receiving and sending messages through the websocket
//it will create websocket at the same port (81)
//for receiving it will parse the received JSON file and update elements
//for sending when click a button or do something will send either JSON file or string to the server
const char index_html[] PROGMEM = R"====(
<!DOCTYPE HTML>
<html>
  <head>
    <title>NodeMCU Car Control Panel</title>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
body{
margin: 0;
padding: 0;
color:rgb(245, 245, 245);
font-family:'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;
font-weight: bolder;
}

.container {
    background-color: aquamarine;
    display: flex;
    flex-direction: column;
    height: 100vh;
}

.topbar {
    
    background-color: #af844c;
    display: flex;
    flex-direction: row;
    flex: 1;
    align-items: center;
    justify-content:left;
    padding: 0 20px;
    border-color: #53291c;
    border-width: 0 0 10px 0;
    box-shadow: 2px 2px 2px rbga(0,0,0,0.3);
    border-style: solid;
}

.toptext {
    color: #fff;
    font-size: 150%;
    text-align: center;
}

.content {
    background-color: #bb9a6f;
    display: flex;
    flex-direction: column;
    align-items: center;
    flex: 14;
}
.empty{
    background-color: #af844c;
    flex:1;
    width: 500px;
    border-color: #53291c;
    border-width: 0 0 10px 0;
    border-top-left-radius: 70px;
    border-top-right-radius: 70px;
    box-shadow: 2px 2px 2px rbga(0,0,0,0.3);
    border-style: solid;
}
.empty2{
    background-color: #867c6f;
    flex:1;
    width: 40%;
}
.panels{
    background-color: #867c6f;
    display: flex;
    flex-direction: column;
    flex:2;
    width: 80%;
    justify-content: flex-start;
    align-items: center;
    border-radius: 100px;
}
.ultrasonicsensorspanels{
    background-color: #af844c;
    display: flex;
    flex-direction: row;
    justify-content: space-between;
    width: 600px;
    border-top-left-radius: 30%;
    border-top-right-radius: 30%;
    border-color: #53291c;
    border-width: 0 5px 10px 5px;
    border-style: solid;
}
.ultrasonicsensorspanel{
    background-color: #af844c;
    display: flex;
    padding: 2%;
    font-size: 150%;
    gap: 10px;
    flex-direction: column;
    align-items: center;
    text-align: center;
    width: 100%;
    border-color: #53291c;
    border-width: 0 5px 5px 5px;
    border-style: solid;
}
.lcdpanels{
    background-color: #af844c;
    display: flex;
    font-size:  200%;
    flex-direction: column;
    align-items: center;
    justify-content:space-around;
    height: 150px;
    width: 600px;
    border-color: #53291c;
    border-width: 0 5px 5px 5px;
    border-style: solid;
}
.lcdpanel{
    background-color: #567443;
    display: flex;
    margin: 5px;
    flex: 1;
    font-size:  200%;
    flex-direction: column;
    justify-content:space-around;
    align-items: center;
    height: 80%;
    width: 500px;
    border-color: #53291c;
    border-width: 5px;
    border-inline: 10px;
    border-style: solid;
}
.inputtextfield{
    border: none;
    background-color: #456830;
    font-size: 50%;
    color: #c2c2c2;
    display: inline-block;
    height: 30%;
    width: 450px;
    text-align: center;
    letter-spacing: 10px;
    font-weight: bold;
}
.inputtextfield:focus{
    background-color: #759463;
}
.inputtextfield::placeholder{
    color: #c2c2c2;
    font-weight: bold;
    
}
.lcdsendbutton{
    width: 250px;
    letter-spacing: 10px;
    color: #1f1c12;
    font-weight: bold;
    background-color: #f5e4cd;
    border-color: #53291c;
    border-width: 5px;
    border-style:outset;
    cursor: pointer;
}
.lcdsendbutton:hover{
    background-color: #c7ac88;
    box-shadow: 4px 4px 4px rgba(0,0,0,0.5);
}
.lcdsendbutton:active{
    transform: scale(0.95);
    box-shadow: 4px 4px 4px rgba(0,0,0,0.5);
}
.servocontrol{
    display: flex;
    justify-content: space-between;
    background-color: darkgrey;
    height: 20%;
    width: 400px;
    border-color: #31333b;
    border-width: 0 5px 5px 5px;
    border-style:outset;
}
.servobutton{
    margin: 2%;
    flex:1;
    height: 80%;
    font-size: larger;
    cursor: pointer;
}
.servostatus{
    background-color: #28538b;
    font-size: larger;
    display: flex;
    flex-direction: column;
    flex: 3;
    justify-content: space-evenly;
    align-items: center;
    border-color: #31333b;
    border-width: 0 10px 5px 10px;
    border-style: outset;
}
.panel2{
    background-color:#ac834d;
    display: flex;
    flex-direction: column;
    flex:1;
    width: 500px;
    justify-content: flex-start;
    align-items: center;
}
.speedcontrolLabel{
    display: flex;
    flex-direction: column;
    background-color: rgb(126, 96, 52);
    align-items: center;
    justify-content:center;
    width: 40%;
    padding: 2%;
    padding-top: 1%;
    padding-bottom: 0%;
    gap: 10px;
    border-color: #53291c;
    border-width: 0 5px 0 5px;
    border-style: solid;
}
.speedcontrolPanel{
    display: flex;
    flex-direction: row;
    background-color: rgb(126, 96, 52);
    justify-content:space-between;
    align-items: center;
    width: 80%;
    padding: 2%;
    padding-top: 1%;
    border-color: #53291c;
    border-width: 0 5px 5px 5px;
    border-style: solid;
}
.slider{
    width: 100%;
    padding: 5px;
    margin: 5px;
    border: 1px inset #53291c;
    appearance: none;
    -webkit-appearance: none;
    background-color: #834343;
    border-radius: 2px;
}
.slider::-webkit-slider-thumb{
    width: 20px;
    height: 20px;
    cursor: pointer;
    border: 1px outset #53291c;
    appearance: none;
    -webkit-appearance: none;
    background-color: #4d300a;
    border-radius: 2px;
}
.slidertext{
    text-align: center;
    width: 10%;
}
.movementPanel{
    background-color: rgb(126, 96, 52);
    justify-self: center;
    display: grid;
    bottom: 0;
    border-radius: 2%;
    border-style: solid;
    border-color: #53291c;
    padding: 2%;
    grid-template-columns: 1fr 1fr 1fr;
    grid-template-rows: 1fr 1fr 1fr;
    grid-gap: 2%;
    height: 100%;
    width: auto;
    justify-self: center;
    justify-content: center;
}

.button{
    display: block;
    width: 100%;
    height: 100%;
    padding: 20px;
    font-size: 150%;
    border-radius: 5%;
    background-color:rgb(145, 113, 75);
    color:rgb(245, 245, 245);
    box-shadow: 2px 2px 2px #53291c;
    text-align: center;
    cursor: pointer;
    user-select: none;
    transition: all 0.2s ease-in-out;
}
.button:hover {
    background-color: rgb(212, 187, 156);
    transform: scale(1.1);
    box-shadow: 4px 4px 4px rgba(0,0,0,0.5);
}
.top {
    grid-row: 1;
    grid-column: 2;
}
.top-left {
    grid-row: 1;
    grid-column: 1;
}
.top-right {
    grid-row: 1;
    grid-column: 3;
}
.left {
    grid-row: 2;
    grid-column: 1;
}
.middle {
    grid-row: 2;
    grid-column: 2;
}
.right {
    grid-row: 2;
    grid-column: 3;
}
.bottom {
    grid-row: 3;
    grid-column: 2;
}
.bottom-left{
    grid-row: 3;
    grid-column: 1;
}
.bottom-right{
    grid-row: 3;
    grid-column: 3;
}
    </style>
	</head>
  <body>
    <div class="container">
      <div class="topbar">
        <span class="toptext">NodeMCU Car Control Panel</span>
      </div>
      <div class="content">
        <div class="panels" id="panels">
          <div class="empty2"></div>
          <div class="ultrasonicsensorspanels">
            <div class="ultrasonicsensorspanel">
              <span>Left Sensor</span>
              <span id="left-sensor-distance">[DISTANCE]</span>
              <span id="left-sensor-status">[STATUS]</span>
            </div>
            <div class="ultrasonicsensorspanel">
              <span>Middle Sensor</span>
              <span id="middle-sensor-distance">[DISTANCE]</span> 
              <span id="middle-sensor-status">[STATUS]</span>
            </div>
            <div class="ultrasonicsensorspanel">
              <span>Right Sensor</span>
              <span id="right-sensor-distance">[DISTANCE]</span>
              <span id="right-sensor-status">[STATUS]</span>
            </div>
          </div>
          <div class="lcdpanels">
            <div class="lcdpanel">
              <input type="text" class="inputtextfield" id="input-row1" placeholder="Hello" maxlength="16">
              <input type="text" class="inputtextfield" id="input-row2" placeholder="World!!" maxlength="16">
            </div>
            <button class="lcdsendbutton" onclick="sendLCDText()">SEND</button>
          </div>
          <div class="servocontrol">
            <button class="servobutton"onclick="rotateServoToLeft()">Turn Left</button>
            <div class="servostatus">
              <span>Servo Rotation</span>
              <span id="current-servo-angle">[Servo Value]</span>
            </div>
            <button class="servobutton" onclick="rotateServoToRight()">Turn Right</button>
          </div>
          <div class="empty"></div>
        </div>
        <div class="panel2">
          <div class="speedcontrolLabel">
            <span>Speed Control</span>
            <span id="slider-value">[SLIDER_VALUE]</span>
          </div>
          <div class="speedcontrolPanel">
            <span class="slidertext"> 0 </span>
            <input class="slider" type="range" min="0" max="255" value="100" oninput = "updateMovementValue(this.value)">
            <span class="slidertext"> 255 </span>
          </div>
          <div class="movementPanel">
            <button class="button top-left" onclick="moveForwardLeft()">↖</button>
            <button class="button top" onclick="moveForward()">↑</button>
            <button class="button top-right" onclick="moveForwardRight()">↗</button>
            <button class="button left" onclick="rotateLeft()">←</button>
            <button class="button middle" onclick="stopMove()">Stop</button>
            <button class="button right" onclick="rotateRight()">→</button>
            <button class="button bottom" onclick="moveBackward()">↓</button>
            <button class="button bottom-left" onclick="moveBackwardLeft()">↙</button>
            <button class="button bottom-right" onclick="moveBackwardRight()">↘</button>
          </div>
        </div>
      </div>
    </div>
  <script>
  var webSocket = new WebSocket('ws://' + window.location.hostname + ':81/');

  webSocket.addEventListener('message', function(event){
    const data = JSON.parse(event.data);

    document.getElementById('left-sensor-status').innerHTML = data.left_sensor_status;
    document.getElementById('middle-sensor-status').innerHTML = data.middle_sensor_status;
    document.getElementById('right-sensor-status').innerHTML = data.right_sensor_status;
    document.getElementById('left-sensor-distance').innerHTML = data.left_sensor_distance + "cm";
    document.getElementById('middle-sensor-distance').innerHTML = data.middle_sensor_distance + "cm";
    document.getElementById('right-sensor-distance').innerHTML = data.right_sensor_distance + "cm";
    document.getElementById("input-row1").placeholder = data.current_LCD_text_row1;
    document.getElementById("input-row2").placeholder = data.current_LCD_text_row2;
    document.getElementById('current-servo-angle').innerHTML = data.current_servo_angle + "°";
    const reading = data.photoResistor_read;

    if (reading === 'Bright') {
      document.getElementById('panels').style.backgroundColor = 'white';
    } else if (reading === 'Dark'){
      document.getElementById('panels').style.backgroundColor = 'black';
    }

  });

  function sendLCDText() {
      var row1 = document.getElementById("input-row1").value;
      var row2 = document.getElementById("input-row2").value;
      var message = {"row1": row1, "row2": row2};
      webSocket.send(JSON.stringify(message));
  }

  function moveForward(){
    webSocket.send("moveForward");
  }
  function moveBackward(){
    webSocket.send("moveBackward");
  }
  function moveForwardLeft(){
    webSocket.send("moveForwardLeft");
  }
  function moveForwardRight(){
    webSocket.send("moveForwardRight");
  }
  function moveBackwardRight(){
    webSocket.send("moveBackwardRight");
  }
  function moveBackwardLeft(){
    webSocket.send("moveBackwardLeft");
  }
  function rotateRight(){
    webSocket.send("rotateRight");
  }
  function rotateLeft(){
    webSocket.send("rotateLeft");
  }  
  function stopMove(){
    webSocket.send("stopMove");
  }
  function rotateServoToRight() {
    webSocket.send("rotateServoToRight");
  }
  function rotateServoToLeft() {
    webSocket.send("rotateServoToLeft");
  }
  function updateMovementValue(val) {
    document.getElementById("slider-value").innerHTML = val;
    webSocket.send("setSpeed," + val);

  }
  </script>
  </body>
</html>
)====";

#endif;