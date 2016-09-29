//
// Created by Rodolfo Castillo Mateluna on 9/29/16.
//

#ifndef PUBLISHER_SENDEREXTENSION_H
#define PUBLISHER_SENDEREXTENSION_H


#include "Sender.h"

class SenderExtension
{
protected:
	Sender & m_sender;

public:
	SenderExtension(Sender & sender);
};


#endif //PUBLISHER_SENDEREXTENSION_H
