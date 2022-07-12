import 'package:flutter/material.dart';
import 'constants.dart';

class ReusableCard extends StatelessWidget {
  final Color? colour;
  final Widget? cardChild;
  final VoidCallback? onPress;

  const ReusableCard({this.colour, this.cardChild, this.onPress});

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: onPress,
      child: Container(
        padding: const EdgeInsets.all(20.0),
        margin: const EdgeInsets.all(8.0),
        decoration: BoxDecoration(
          color: colour,
          borderRadius: BorderRadius.circular(10.0),
        ),
        child: cardChild,
      ),
    );
  }
}

class DeviceCard extends StatefulWidget {
  final String? deviceName;
  final Widget? cardChild;
  final Function(bool)? onPress;
  Color? inactiveColor;
  bool value = false;


  DeviceCard({this.deviceName, this.cardChild, this.onPress, required this.value,this.inactiveColor});

  @override
  State<DeviceCard> createState() => _DeviceCardState();
}

class _DeviceCardState extends State<DeviceCard> {
  @override
  Widget build(BuildContext context,) {
    return Container(
      padding: const EdgeInsets.all(20.0),
      margin: const EdgeInsets.all(8.0),
      decoration: BoxDecoration(
        color: kActiveCardColor,
        borderRadius: BorderRadius.circular(10.0),
      ),
      child: Row(
        mainAxisAlignment: MainAxisAlignment.spaceBetween,
        children: [
          Text(widget.deviceName!,
            style: kLableTextStyle,
          ),

          Switch(
            activeColor: kSwitchActiveColor,
            value: widget.value,
            onChanged: widget.onPress!,
            inactiveTrackColor: widget.inactiveColor,
          ),
        ],
      ),
    );
  }
}

class LockCard extends StatefulWidget {
  final String? deviceName;
  final Widget? cardChild;
  final void Function()? onPress;
  bool? value = false;


  LockCard({this.deviceName, this.cardChild, this.onPress, this.value});

  @override
  State<LockCard> createState() => _LockCardState();
}

class _LockCardState extends State<LockCard> {
  @override
  Widget build(BuildContext context,) {
    return Container(
      // height: 80,
      padding: const EdgeInsets.all(20.0),
      margin: const EdgeInsets.all(8.0),
      decoration: BoxDecoration(
        color: kActiveCardColor,
        borderRadius: BorderRadius.circular(10.0),
      ),
      child: Row(
        mainAxisAlignment: MainAxisAlignment.spaceBetween,
        children: [
          Text(widget.deviceName!,
            style: kLableTextStyle,
          ),

          FlatButton(
            onPressed: widget.onPress,
            child: Text("open"),
            color: kSwitchActiveColor,
          ),
        ],
      ),
    );
  }
}

