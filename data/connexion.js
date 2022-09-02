var url = "192.168.4.1/ws"   //"192.168.42.124:5000" //"192.168.42.226/ws"; //https://socketsbay.com/test-websockets
var ws = new WebSocket("ws://" + url);
var last_cmd_stamp = 1.0; //used to timeout and prevent user to send too many request quickly

//Websocket callbacks : 
ws.onopen = function(evt) { 
    document.getElementById("connexion_status").innerHTML = "Connecté" 
};
ws.onclose = function(evt) {
    document.getElementById("connexion_status").innerHTML = "Déconnecté"
 };
ws.onerror = function(evt) { 
    document.getElementById("connexion_status").innerHTML = "Erreur connexion : " + evt.data 
    console.log("erreur : " + evt.data);
    console.log("url tried for debug purposes : " + url);
};

ws.onmessage = function(evt) { 
    //if format correct
    //Parse command majoritaire and nb connecté/nb pour la cmd
    console.log( "Received Message: " + evt.data); 
    document.getElementById("cmd_status").innerHTML = evt.data
};


//check last timestamp and return true if timeout for sending another command is exceeded
//update the timer
function check_stamp() { 
    if(Date.now() - last_cmd_stamp > 250) { 
        last_cmd_stamp = Date.now();
        return true;
    }
    return false;
}
//Trigger forward when the button is clicked 
function forward(params) {
    if(check_stamp()) {
        ws.send("f");
    }
}

function backward(params) {
    if(check_stamp()) {
        ws.send("b");
    }
}

function left(params) {
    if(check_stamp()) {
        ws.send("l");
    }
}

function right(params) {
    if(check_stamp()) {
        ws.send("r");
    }
}

function stop(params) {
    if(check_stamp()) {
        ws.send("s");
    }
}