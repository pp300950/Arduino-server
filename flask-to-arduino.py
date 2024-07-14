from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('http://192.168.60.155/ledstatus', methods=['POST'])
def receive_led_status():
    data = request.json  
    led_status = data.get('led_status')  #ดึงข้อมูลสถานะLEDจาก JSON

    #ทำอะไรกับข้อมูลสถานะLEDต่อไปนี้
    print("Received LED status:", led_status)

    #ส่งข้อมูลยืนยันการรับข้อมูลกลับไปยังESP8266
    response_data = {'message': 'LED status received successfully'}
    return jsonify(response_data)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
