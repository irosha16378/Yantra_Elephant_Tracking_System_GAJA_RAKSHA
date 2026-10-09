import os
from flask import Flask, render_template, jsonify

app = Flask(__name__, template_folder='templates', static_folder='static')

# Log memory storage for live dashboard
detection_logs = [
    {
        'img': 'snapshots/sample.jpg',
        'time': '2026-10-09 21:30:00',
        'status': 'ELEPHANT DETECTED',
        'zone': 'North Corridor',
        'action': 'Robot Stopped / Alarm Triggered'
    }
]

@app.route('/')
def index():
    return render_template('index.html', logs=detection_logs)

@app.route('/api/logs')
def get_logs():
    return jsonify(detection_logs)

if __name__ == '__main__':
    print("[SERVER] Starting GajaRaksha Web Command Center at http://localhost:5000")
    app.run(host='0.0.0.0', port=5000, debug=True)
