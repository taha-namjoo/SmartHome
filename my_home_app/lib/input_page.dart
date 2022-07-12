import 'package:flutter/material.dart';
import 'reusable_card.dart';
import 'constants.dart';
import 'package:mqtt_client/mqtt_client.dart';
import 'mqtt_wildCard.dart';


// Future<MqttServerClient> clientFuture = mqttInit();

class InputPage extends StatefulWidget {
  @override
  _InputPageState createState() => _InputPageState();
}

class _InputPageState extends State<InputPage> {
  int temperature = 25;
  bool lamp = false;
  bool AC = false;
  bool ACpump = false;
  bool ACmotor = false;
  bool ACspeed = false;
  Mqtt client = Mqtt();


  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Scaffold(
        appBar: AppBar(
          title: Center(child: Text('SMART HOME')),
          backgroundColor: Color(0xFF101020),
        ),
        body: ListView(
          children: [
            DeviceCard(
              deviceName: 'lamp',
              value: lamp,
              inactiveColor: Colors.pink.withOpacity(0.5),
              onPress: (value) {
                if (client.client.connectionStatus!.state !=
                    MqttConnectionState.connected) {
                  showDialog(
                      context: context,
                      builder: (context) {
                        return AlertDialog(
                          title: Text('connecting...'),
                          titleTextStyle:
                              TextStyle(fontSize: 17, color: Colors.white),
                          actions: [
                            TextButton(
                              child: Text(
                                'OK',
                                style: TextStyle(
                                    fontSize: 17,
                                    color: Colors.lightBlueAccent),
                              ),
                              onPressed: () {
                                Navigator.pop(context);
                              },
                            ),
                          ],
                        );
                      });
                } else {
                  setState(() {
                    lamp = lamp ? false : true;
                  });
                  client.sendMessage("lamp", lamp ? "1" : "0");
                }
              },
            ),
            LockCard(
              deviceName: 'door lock',
              onPress: () {
                if(client.client.connectionStatus!.state != MqttConnectionState.connected){
                  showDialog(
                      context: context,
                      builder: (context) {
                        return AlertDialog(
                          title: Text('connecting...'),
                          titleTextStyle: TextStyle(
                              fontSize: 17, color: Colors.white),
                          actions: [
                            TextButton(
                              child: Text(
                                'OK',
                                style: TextStyle(
                                    fontSize: 17,
                                    color: Colors.lightBlueAccent),
                              ),
                              onPressed: () {
                                Navigator.pop(context);
                              },
                            ),
                          ],
                        );
                      });
                }else{
                client.sendMessage("doorLock", "L");
              }},
            ),
            ReusableCard(
              colour: kActiveCardColor,
              cardChild: Column(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  DeviceCard(
                    deviceName: 'Air Conditioner',
                    value: AC,
                    inactiveColor: Colors.pink.withOpacity(0.5),
                    onPress: (value) {
                      if (client.client.connectionStatus!.state !=
                          MqttConnectionState.connected) {
                        showDialog(
                            context: context,
                            builder: (context) {
                              return AlertDialog(
                                title: Text('connecting...'),
                                titleTextStyle: TextStyle(
                                    fontSize: 17, color: Colors.white),
                                actions: [
                                  TextButton(
                                    child: Text(
                                      'OK',
                                      style: TextStyle(
                                          fontSize: 17,
                                          color: Colors.lightBlueAccent),
                                    ),
                                    onPressed: () {
                                      Navigator.pop(context);
                                    },
                                  ),
                                ],
                              );
                            });
                      } else {
                        setState(() {
                          AC = AC ? false : true;
                          ACpump = AC ? ACpump : false;
                          ACmotor = ACpump ? ACmotor : false;
                          ACspeed = ACmotor ? ACspeed : false;
                          // print(value);
                        });
                        if (!AC) {
                          client.sendMessage("AC", "0");
                        }
                      }
                    },
                  ),
                  DeviceCard(
                    deviceName: 'A/C water pump',
                    value: ACpump,
                    inactiveColor: AC
                        ? Colors.pink.withOpacity(0.5)
                        : Colors.grey.withOpacity(0.3),
                    onPress: (value) {
                      if (client.client.connectionStatus!.state !=
                          MqttConnectionState.connected) {
                        showDialog(
                            context: context,
                            builder: (context) {
                              return AlertDialog(
                                title: Text('connecting...'),
                                titleTextStyle: TextStyle(
                                    fontSize: 17, color: Colors.white),
                                actions: [
                                  TextButton(
                                    child: Text(
                                      'OK',
                                      style: TextStyle(
                                          fontSize: 17,
                                          color: Colors.lightBlueAccent),
                                    ),
                                    onPressed: () {
                                      Navigator.pop(context);
                                    },
                                  ),
                                ],
                              );
                            });
                      } else {
                        if (AC == false) {
                          return null;
                        }
                        setState(() {
                          ACpump = ACpump ? false : true;
                          ACmotor = ACpump ? ACmotor : false;
                          ACspeed = ACmotor ? ACspeed : false;
                          // print(value);
                        });
                        client.sendMessage("ACpump", ACpump ? "1" : "0");
                      }
                    },
                  ),
                  DeviceCard(
                    deviceName: 'A/C motor',
                    value: ACmotor,
                    inactiveColor: AC && ACpump
                        ? Colors.pink.withOpacity(0.5)
                        : Colors.grey.withOpacity(0.3),
                    onPress: (value) {
                      if (client.client.connectionStatus!.state !=
                          MqttConnectionState.connected) {
                        showDialog(
                            context: context,
                            builder: (context) {
                              return AlertDialog(
                                title: Text('connecting...'),
                                titleTextStyle: TextStyle(
                                    fontSize: 17, color: Colors.white),
                                actions: [
                                  TextButton(
                                    child: Text(
                                      'OK',
                                      style: TextStyle(
                                          fontSize: 17,
                                          color: Colors.lightBlueAccent),
                                    ),
                                    onPressed: () {
                                      Navigator.pop(context);
                                    },
                                  ),
                                ],
                              );
                            });
                      } else {
                        if (!AC || !ACpump) {
                          return null;
                        }
                        setState(() {
                          ACmotor = ACmotor ? false : true;
                          ACspeed = ACmotor ? ACspeed : false;
                          // print(value);
                        });
                        client.sendMessage("ACmotor", ACmotor ? "1" : "0");
                      }
                    },
                  ),
                  DeviceCard(
                    deviceName: 'A/C speed',
                    value: ACspeed,
                    inactiveColor: AC && ACmotor
                        ? Colors.pink.withOpacity(0.5)
                        : Colors.grey.withOpacity(0.3),
                    onPress: (value) {
                      if (client.client.connectionStatus!.state !=
                          MqttConnectionState.connected) {
                        showDialog(
                            context: context,
                            builder: (context) {
                              return AlertDialog(
                                title: Text('connecting...'),
                                titleTextStyle: TextStyle(
                                    fontSize: 17, color: Colors.white),
                                actions: [
                                  TextButton(
                                    child: Text(
                                      'OK',
                                      style: TextStyle(
                                          fontSize: 17,
                                          color: Colors.lightBlueAccent),
                                    ),
                                    onPressed: () {
                                      Navigator.pop(context);
                                    },
                                  ),
                                ],
                              );
                            });
                      } else {
                        if (!AC || !ACmotor) {
                          return null;
                        }
                        setState(() {
                          ACspeed = ACspeed ? false : true;
                        });
                        client.sendMessage("ACspeed", ACspeed ? "1" : "0");
                      }
                    },
                  ),
                ],
              ),
            ),
          ],
        ),
      ),
    );
  }
}
