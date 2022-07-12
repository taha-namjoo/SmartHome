import 'dart:io';
import 'package:mqtt_client/mqtt_client.dart';
import 'package:mqtt_client/mqtt_server_client.dart';

class Mqtt{
  final client = MqttServerClient('mqtt.mdhi.dev', '');
  Mqtt(){
    mqttInit();
  }
  mqttInit() async{
    client.logging(on: false);

    client.setProtocolV311();

    client.keepAlivePeriod = 30;

    client.onDisconnected = onDisconnected;

    final connMess = MqttConnectMessage()
        .withClientIdentifier('Mqtt_MyClientUniqueIdWildcard')
        .withWillTopic('willtopic') // If you set this you must set a will message
        .withWillMessage('My Will message')
        .startClean() // Non persistent session for testing
        .withWillQos(MqttQos.atLeastOnce);
    print('Mosquitto client connecting....');
    client.connectionMessage = connMess;

    try {
      await client.connect("smarthome","troplonglaissetomber");
    } on Exception catch (e) {
      print('client exception - $e');
      client.disconnect();
    }

    /// Check we are connected
    if (client.connectionStatus!.state == MqttConnectionState.connected) {
      print('Mosquitto client connected');
    } else {
      print(
          'ERROR Mosquitto client connection failed - disconnecting, state is ${client.connectionStatus!.state}');
      client.disconnect();
      exit(-1);
    }
    client.autoReconnect = true;
    client.subscribe("smarthome/#", MqttQos.atLeastOnce);
  }

  /// The unsolicited disconnect callback
  void onDisconnected() {
    print('OnDisconnected client callback - Client disconnection');
  }


  void sendMessage(String topic,String message){
    final builder1 = MqttClientPayloadBuilder();
    builder1.addString(message);
    print('<<<< PUBLISH $message on smarthome/$topic >>>>');
    client.publishMessage("smarthome/$topic", MqttQos.atLeastOnce, builder1.payload!);
  }
}

