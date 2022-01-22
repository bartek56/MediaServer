import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.1
import QuotesLib 1.0

Dialog
{
    id: quotesDialog
    visible: true
    width: 800
    height: 480
    margins: 0
    padding: 1
    modal: true

    property string imageLink: ""
    property string authorEnglish: ""
    property string quoteEnglish: ""
    property string authorPolish: ""
    property string quotePolish: ""

    Quotes{
        id: quotes
    }

    function request_test() {
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function() {
            if(xhr.readyState === XMLHttpRequest.DONE)
            {
                var responseString = xhr.responseText.toString();
                var response = JSON.parse(responseString);
                quoteEnglish = response.content;
                authorEnglish = response.author;
                imageLink = "https://theysaidso.com/img/qod/qod-inspire.jpg"
            }
        }
        xhr.open("GET", "https://api.quotable.io/random");
        xhr.send();
    }

    function request() {
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function() {
            if(xhr.readyState === XMLHttpRequest.DONE)
            {
                var responseString = xhr.responseText.toString();
                var response = JSON.parse(responseString);
                quoteEnglish = response.contents.quotes[0].quote;
                authorEnglish = response.contents.quotes[0].author;
                imageLink = response.contents.quotes[0].background;
            }
        }
        xhr.open("GET", "https://quotes.rest/qod", true);
        xhr.send();
    }

    Image {
        id: name
        source: imageLink
    }

    Text {
        id: englishQuoteText
        x: 35
        y: 31
        width: 700
        height: 105
        text: quoteEnglish
        fontSizeMode: Text.Fit
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
        font.pixelSize: 25
    }

    Text {
        id: authorEnglishText
        x: 404
        y: 151
        width: 351
        height: 40
        text: authorEnglish
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 24
    }

    Text {
        id: polishQuoteText
        x: 35
        y: 210
        width: 700
        height: 105
        text: quotePolish
        font.pixelSize: 25
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignBottom
        wrapMode: Text.WordWrap
        fontSizeMode: Text.Fit
    }

    Text {
        id: polishAuthorText
        x: 404
        y: 321
        width: 351
        height: 40
        text: authorPolish
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 24
    }

    Button {
        x: 60
        y: 396
        opacity: 0.5
        text: qsTr("Save and Close")
        onClicked: {
            quotes.save(quoteEnglish.toString(), authorEnglish.toString(),
                        quotePolish.toString(), authorPolish.toString())
                Qt.callLater(Qt.quit)
        }
    }

    Button {
        x: 646
        y: 396
        opacity: 0.5
        text: qsTr("Close")
        onClicked:
        {
            Qt.callLater(Qt.quit)
        }
    }

    Component.onCompleted:
    {
//        request_test()
        request()
        quotes.getQuote(quotesDialog)
    }
}
