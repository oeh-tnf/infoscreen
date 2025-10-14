import QtQuick 6.0
import QtQuick.Controls 6.0
import oeh.jku.tnf.infoscreen 1

Item {    
	LinzAGDepartureSource {
		id: linzag_source_uni
		stopId: "at:44:41101"
	}
	
	Timer {
		interval: 60000
		running: true
		repeat: true
		triggeredOnStart: true
		onTriggered: linzag_source_uni.load()
	}

	TableView {
		id: departure_table
		anchors.fill: parent
		animate: false
		
		model: LinzAGDepartureModel {
			id: linzag_model_uni
			json: linzag_source_uni.json
		}
		
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

	Timer {
		interval: 1000
		running: true
		repeat: true
		triggeredOnStart: true
		onTriggered: { linzag_model_uni.now = new Date() }
	}
}

