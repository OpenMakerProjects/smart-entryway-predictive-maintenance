# Architecture

The shared Maintenance policy debounces a reed input for 50ms, counts closed-to-open transitions, and computes a rule-based service reminder at 1000 cycles or 30 seconds continuously open. Ambient light is an independent status channel. Firmware samples every ~10ms, drives an RGB indicator and prints JSON every 2 seconds. Everything is local and volatile.
