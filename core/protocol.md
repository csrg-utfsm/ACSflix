# Protocol

This protocol is based on ZeroMQ frame messages, each line of the packet is a different frame.

## HOLA

The receiver shall contact the server, the contents of this packet are optional.

    IP
    PORT
    MACHINE_NAME

## SETS

The emitter shall send settings to the receiver.

    BLOCK_SIZE (bytes)

## SETK

The receiver shall acknowledge and send back receiver specific settings.

    BLOCK_SIZE      in any normal case this is the same as the SETS package, but some server could specify more
                    capacity or less, the emitter should choose the minimum.
    CREDITS         maximum quantity of credits the receiver supports, the emitter should use this just for status.

## CREA

The receiver shall let the emitter know that it has the capacity for another packet, the content of this packet is
blank.

## TAKE

The emitter shall send a TAKE packet with the contents of the next section of the file.

## DONE

The emitter shall send a DONE packet when there's no more content to send. The content of this packet is blank.
