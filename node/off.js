var mqtt = require('mqtt')
var config = require('./config');

var client  = mqtt.connect(config.server, {
    username: config.username,
    password: config.password
});

client.on('connect', function () {
  client.publish(`workshop/${config.device}/led`, 'OFF');
  client.end();
});
