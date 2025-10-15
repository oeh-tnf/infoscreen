import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 6.0

ColumnLayout {
	id: root

	required property var time
	required property var departures

	Rectangle {
		Layout.fillWidth: true
		Layout.preferredHeight: 80;

		color: "#000000"

		RowLayout {
			anchors.fill: parent;

			Item {
				Layout.fillWidth: true
				Layout.fillHeight: true
			}

			Text {
				Layout.fillHeight: true

				color: "#ffffff"

				padding: 20
				font.pointSize: 30
				verticalAlignment: Text.AlignVCenter

				text: root.time.toLocaleTimeString("de-AT")
			}
		}
	}

	TableView {
		id: departure_table

		Layout.fillWidth: true
		Layout.fillHeight: true

		animate: false
		
		model: root.departures
		
		property var columnAlignments: [Text.AlignHCenter, Text.AlignLeft, Text.AlignRight]
		
		delegate: Rectangle {
			color: row % 2 == 0 ? "#ffffff" : "#efefef"
			
			Text {
				anchors.fill: parent
				text: display
				padding: 20
				font.pointSize: 40
				verticalAlignment: Text.AlignVCenter
				horizontalAlignment: departure_table.columnAlignments[column]
			}
		}
		
		columnWidthProvider: (column) => {
			if (column == 0) {
				return 150;
			} else if (column == 1) {
				return departure_table.width - 150 - 150;
			} else if (column == 2) {
				return 150;
			}
		}
		
		rowHeightProvider: (row) => 100 
	}
}

