from picamera import PiCamera
from time import sleep

#script for taking photos, not finished

cam = PiCamera()

cam.start_preview()
cam.capture_sequence()
cam.stop_preview()
