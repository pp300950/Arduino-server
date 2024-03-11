from flask import Flask, request, jsonify

app = Flask(__name__)

# เส้นทาง URL สำหรับรับข้อมูลสถานะ LED จาก ESP8266
@app.route('http://192.168.60.155/ledstatus', methods=['POST'])
def receive_led_status():
    data = request.json  # รับข้อมูล JSON จาก ESP8266
    led_status = data.get('led_status')  # ดึงข้อมูลสถานะ LED จาก JSON

    # ทำอะไรกับข้อมูลสถานะ LED ต่อไปนี้
    print("Received LED status:", led_status)

    # ส่งข้อมูลยืนยันการรับข้อมูลกลับไปยัง ESP8266
    response_data = {'message': 'LED status received successfully'}
    return jsonify(response_data)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
