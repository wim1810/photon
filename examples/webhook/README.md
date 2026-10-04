# Photon webhook example

1. Edit `url` in `webhook.json`, then register it:
   `particle webhook create examples/webhook/webhook.json`
2. Flash the firmware: `particle flash <device> examples/webhook/webhook.ino`
3. Press the button on D3; the Photon publishes `temp-alert` and the Particle
   cloud POSTs the JSON to your URL. The server's reply returns as
   `hook-response/temp-alert`.

The Photon cannot host an inbound webhook server directly (it sits behind
NAT). To trigger the Photon from outside, call a cloud function:
`Particle.function("led", handler)` and POST to
`https://api.particle.io/v1/devices/<id>/led`.
