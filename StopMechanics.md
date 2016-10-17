# Stop Mechanics

## ID + Timeout Way

Track all workers to a ID set, when stop() is called send
a stop signal to all of them.

Assume all workers will receive the message within
the linger time.

Problem is: does ZeroMQ knows how to skip the send queue
if a receiver is down, or it waits there until is able
to send the message.

## Token + Timeout Way

Use tokens to track which workers are currently up, when
one token is received, send a stop signal, the way to know
when to stop receiving is via a timeout.
