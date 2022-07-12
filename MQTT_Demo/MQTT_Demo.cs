using System;
using System.Net;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;

[Serializable]
public class JsonClass
{
    public string id;
    public int power;
}

public class MQTT_Demo : MonoBehaviour
{
    JsonClass JsonObject = new JsonClass();
    private MqttClient client;
    public string[] ESP_ID = new string[] { "840152", "762392", "653254" ,"666777"};
    public int[] ESP_Trigger = new int[] { 0, 0, 0 };
    string pub = "Light";

    bool TriggerSwitch = true;

    void Start()
    {
        string txtIP = "210.68.227.123";
        string txtPort = "3881";
        string clientId = Guid.NewGuid().ToString();
        string username = "acme";
        string password = "85024828";
        client = new MqttClient(IPAddress.Parse(txtIP), int.Parse(txtPort), false, null);

        client.MqttMsgPublishReceived += Client_MqttMsgPublishReceived;
        client.MqttMsgSubscribed += Client_MqttMsgSubscribed;
        client.Connect(clientId, username, password);
        client.Subscribe(
            new string[] { "Light" },
            new byte[] { MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE }
        );
    }

    void SendMQTT(string pub, string val)
    {
        client.Publish(
            pub,
            System.Text.Encoding.UTF8.GetBytes(val),
            MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE,
            false
        );
    }

    public void LightOnClick(int val)
    {
        JsonObject.id = ESP_ID[val];
        if (TriggerSwitch == true)
        {
            JsonObject.power = ESP_Trigger[0];
            TriggerSwitch = false;
        }
        else if (TriggerSwitch == false)
        {
            JsonObject.power = ESP_Trigger[1];
            TriggerSwitch = true;
        }
        string json = JsonUtility.ToJson(JsonObject);
        SendMQTT("Light", json);
    }
    
    public void DoorOnClick(int val)
    {
        JsonObject.id = ESP_ID[val];
        JsonObject.power = ESP_Trigger[val];
        string json = JsonUtility.ToJson(JsonObject);
        SendMQTT("Door", json);
    }

    private void Client_MqttMsgSubscribed(object sender, MqttMsgSubscribedEventArgs e)
    {
        //Debug.Log("Subscribed" + e.MessageId);
    }

    private void Client_MqttMsgPublishReceived(object sender, MqttMsgPublishEventArgs e)
    {
        string message = System.Text.Encoding.UTF8.GetString(e.Message);
        JsonObject = JsonUtility.FromJson<JsonClass>(message);

        Debug.Log(message);
        Debug.Log("id:" + JsonObject.id + ",power:" + JsonObject.power);
    }
}
