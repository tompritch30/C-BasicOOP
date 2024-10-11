#include <string>
#include <utility>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>

using namespace std;


class Text;

class Sheet {
private:
    int width;
    int height;
    int currentWidth;
    int currentHeight;

public:
    Sheet(int _width, int _height);


    void printText(Text *text);

};

Sheet::Sheet(int _width, int _height) : width(_width), height(_height), currentWidth(0), currentHeight(0) {}


class Text {
protected:
    string text;
    int lineCount;
public:
    Text(string _text);

    string getText(){
        return getPrefix() + text + "\n" + getPostfix();
    }

    string virtual getPrefix() const = 0;
    string virtual getPostfix() const = 0;

    void setCount(int count);

    int getLength();
};

void Sheet::printText(Text *text) {
    string itemText = text->getText();
    for (int i = 0; i < itemText.size(); i++){
        cout << itemText[i];
        currentWidth = i;
        if (currentWidth > width){
            cout << "\n";
            currentHeight++;
            if (currentHeight > height){
                cout << "Warning page size exceeded" << endl;
            }
            currentWidth = 0;
        }
    }

}


Text::Text(string _text) : text(_text), lineCount(1) {}

void Text::setCount(int count) {
    lineCount = count;
}

int Text::getLength() {
    return text.size();
}


class Paragraph: public Text {
public:
    Paragraph(string _text);

    string getPrefix() const override;
    string getPostfix() const override;
};

Paragraph::Paragraph(string _text) : Text(_text) {}

string Paragraph::getPrefix() const {
    return "  ";
}

string Paragraph::getPostfix() const {
    return "\n";
}

class Heading: public Text  {
public:
    Heading(string _text);

    string getPrefix() const override;
    string getPostfix() const override;

};

Heading::Heading(std::string _text) : Text(_text) {}

string Heading::getPrefix() const {
    return to_string(lineCount) + ". ";
}

string Heading::getPostfix() const {
    return "";
}


class LeafLet {
private:
    int id;
    int lineCount = 1;
    Sheet* sheet;
    queue<Text*> textQueue;
    bool addedHeader = false;

    int currentSize = 0;

public:
    LeafLet(int id);

    void addHeader(Text *headerText);

    void addParagraph(Text *paragraphText);

    void addSheet(Sheet * _sheet);

    void printSheet();


};

void LeafLet::addParagraph(Text *paragraphText) {
    if (addedHeader || currentSize + paragraphText->getLength() > 1000 ){
        cout << "Added paragraph: " << paragraphText->getText() << endl;
        textQueue.push(paragraphText);
        // headerText->setCount(lineCount++);
        addedHeader = false;
        currentSize += paragraphText->getLength();
    } else {
        cout << "You need to add a header first" << endl;
    }
}

void LeafLet::printSheet() {
    while(!textQueue.empty()){
        Text* output = textQueue.front();
        // cout << "testprint sheet output" << output->getText() << endl;
        textQueue.pop();
        sheet->printText(output);
    }
    // sheet->printContent();
}

void LeafLet::addSheet(Sheet * _sheet) {
    sheet = _sheet;
}

void LeafLet::addHeader(Text *headerText) {
    if (!addedHeader || currentSize + headerText->getLength() > 1000 ){
        cout << "Added header: " << headerText->getText() << endl;
        textQueue.push(headerText);
        headerText->setCount(lineCount++);
        addedHeader = true;
        currentSize += headerText->getLength();
    } else {
        cout << "You need to add a paragraph first" << endl;
    }
}

LeafLet::LeafLet(int _id): id(_id) {

}



//int main() {
//    // cout << "test";
//    LeafLet leafLet = LeafLet(1);
//    Sheet smallSheet = Sheet(50, 50);
//    Sheet tinySheet = Sheet(20, 40);
//
//
//    Heading beesHeader = Heading("Importance of the Bees");
//    Paragraph beesParagraph = Paragraph("Bees are important because ...");
//    leafLet.addHeader(&beesHeader);
//    leafLet.addParagraph(&beesParagraph);
//
//    Heading beeThreatsHeader = Heading("Threats to Bees");
//    Paragraph beeThreatsParagraph = Paragraph("Significant threats ...");
//    leafLet.addHeader(&beeThreatsHeader);
//    leafLet.addParagraph(&beeThreatsParagraph);
//
//    leafLet.addSheet(&smallSheet);
//    leafLet.printSheet();
//    leafLet.addSheet(&tinySheet);
//    leafLet.printSheet();
//
//    return 0;
//}
//
