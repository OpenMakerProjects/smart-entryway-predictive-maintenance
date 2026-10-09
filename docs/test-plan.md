# Test plan

Cloud host tests exercise bounce rejection, transition counting, boot-open behavior, long-open and cycle thresholds, saturation, reset conditions and 32-bit timer wrap. CI compiles the actual Nano 33 IoT target. On hardware, first test disconnected USB-powered circuit continuity; close/open the contact and compare serial JSON, hold open 30 seconds, then send RESET after closing. Hardware tests remain unperformed.
