import cv2
import requests
import numpy as np
import time

CAM_URL = "http://192.168.106.176/capture"
AGV_IP = "192.168.106.202"

destination = input("Enter Destination (A/B/C): ").strip().upper()

detector = cv2.QRCodeDetector()

last_qr = ""
last_time = 0

while True:

    try:

        response = requests.get(CAM_URL, timeout=5)

        img_array = np.asarray(
            bytearray(response.content),
            dtype=np.uint8
        )

        frame = cv2.imdecode(
            img_array,
            cv2.IMREAD_COLOR
        )

        if frame is None:
            continue

        data, bbox, _ = detector.detectAndDecode(frame)

        current_time = time.time()

        if data and (
            data != last_qr or
            current_time - last_time > 3
        ):

            print("QR Detected:", data)

            last_qr = data
            last_time = current_time

            if data == destination:

                print("Destination Match")

                if destination == "A":

                    print("LEFT")
                    requests.get(
                        f"http://{AGV_IP}/left"
                    )

                elif destination == "B":

                    print("RIGHT")
                    requests.get(
                        f"http://{AGV_IP}/right"
                    )

                elif destination == "C":

                    print("FORWARD")
                    requests.get(
                        f"http://{AGV_IP}/forward"
                    )

        cv2.imshow("ESP32-CAM QR", frame)

        if cv2.waitKey(1) & 0xFF == 27:
            break

    except Exception as e:

        print("Error:", e)

cv2.destroyAllWindows()