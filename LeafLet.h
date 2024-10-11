//
// Created by thoma on 22/04/2024.
//

#ifndef PPP_LEAFLET_H
#define PPP_LEAFLET_H


#include "Text.h"
#include "Sheet.h"

class LeafLet {

public:
    void addHeader(Text *headerText);

    void addParagraph(Text *paragraphText);

    void addSheet(Sheet *sheet);

    void printSheet();
};


#endif //PPP_LEAFLET_H
