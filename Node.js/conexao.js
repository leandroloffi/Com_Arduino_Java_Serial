
const deviceModule = require('..').device;
const cmdLineProcess = require('./lib/cmdline');

var myThingName = 'Minha_Raspberry3';

//begin module

function processTest(args) {
	
   const device = deviceModule({
      keyPath: args.privateKey,
      certPath: args.clientCert,
      caPath: args.caCert,
      clientId: args.clientId,
      region: args.region,
      baseReconnectTimeMs: args.baseReconnectTimeMs,
      keepalive: args.keepAlive,
      protocol: args.Protocol,
      port: args.Port,
      host: args.Host,
      debug: args.Debug
   });

   var timeout;
   var count = 0;
   const minimumDelay = 250;

   if (args.testMode === 1) {
      device.subscribe('topic_1');
   } else {
      device.subscribe('topic_2');
   }
   if ((Math.max(args.delay, minimumDelay)) !== args.delay) {
      console.log('substituting ' + minimumDelay + 'ms delay for ' + args.delay + 'ms...');
   
   }
   device.on('connect', function() {
		 console.log("CONECTANDO...");
         console.log("REGISTRANDO...");
		 console.log("TRABALHANDO...");
    });
   setInterval(function() {
		data = {'temp': parseFloat(34), 'hum': parseFloat(35), 'wat': parseFloat(36), 'sol': parseFloat(37)}
		device.publish('sensor/data', JSON.stringify(data));
	}, 20000);

   
    device.on('close', function() {
         console.log('close');
    });
    device.on('reconnect', function() {
         console.log('reconnect');
    });
    device.on('offline', function() {
         console.log('offline');
    });
	device.on('error', function(error) {
		console.log('error', error);
	});
   device.on('message', function(topic, payload) {
         console.log('message', topic, payload.toString());
    });
}

module.exports = cmdLineProcess;

if (require.main === module) {
   cmdLineProcess('connect to the AWS IoT service and publish/subscribe to topics using MQTT, test modes 1-2',
      process.argv.slice(2), processTest);
}
