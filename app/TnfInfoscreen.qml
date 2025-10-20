import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 6.0

ColumnLayout {
	id: root

	required property var time
	required property var departures
	required property var jku_mensa
	required property var khg_mensa

	spacing: 0
	
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

				text: root.time.time.toLocaleTimeString("de-AT")
			}
		}
	}

	RowLayout {
		Layout.fillWidth: true
		Layout.fillHeight: true

		spacing: 0

		TableView {
			id: departure_table

			Layout.fillHeight: true
			Layout.fillWidth: true

			animate: false
			clip: true
			
			model: root.departures
			
			property var columnAlignments: [Text.AlignHCenter, Text.AlignLeft, Text.AlignRight]
			
			delegate: Rectangle {
				color: row % 2 == 0 ? "#ffffff" : "#efefef"
				
				Text {
					anchors.fill: parent
					elide: Text.ElideRight
					text: display
					padding: 10
					font.pointSize: 40
					verticalAlignment: Text.AlignVCenter
					horizontalAlignment: departure_table.columnAlignments[column]
				}
			}
			
			columnWidthProvider: (column) => {
				if (column == 0) {
					return 120;
				} else if (column == 1) {
					return departure_table.width - 120 - 120;
				} else if (column == 2) {
					return 120;
				}
			}
			
			rowHeightProvider: (row) => 100 
		}
		
		StackLayout {
			Layout.fillHeight: true
			Layout.fillWidth: true

			Timer {
				interval: 5000; running: true; repeat: true
				onTriggered: parent.currentIndex = (parent.currentIndex + 1) % parent.count;
			}

			Rectangle {
				Layout.fillWidth: true
				Layout.fillHeight: true

				color: "#fbb601"
				ColumnLayout {
					anchors.fill: parent

					Text {
						Layout.fillWidth: true

						padding: 20

						color: "#ffffff"
						font.weight: Font.Bold
						font.pointSize: 30

						text: "JKU Mensa"
					}

					ListView {
						id: jku_mensa_menu

						Layout.fillWidth: true
						Layout.fillHeight: true

						spacing: 20

						model: jku_mensa

						delegate: Rectangle {
							anchors.left: parent.left
							anchors.right: parent.right
							anchors.leftMargin: 20
							anchors.rightMargin: 20

							height: (jku_mensa_menu.height - (jku_mensa_menu.count*20)) / jku_mensa_menu.count

							radius: 20
							color: "#ffffff"

							Text {
								anchors.fill: parent
								clip: true
								verticalAlignment: Text.AlignVCenter
								wrapMode: Text.WordWrap
								padding: 30
								color: "#000000"
								font.pointSize: 20
								text: display
							}
						}
					}
				}
			}

			Rectangle {
				Layout.fillWidth: true
				Layout.fillHeight: true

				color: "#ac1410"

				ColumnLayout {
					anchors.fill: parent

					Text {
						Layout.fillWidth: true

						padding: 20

						color: "#ffffff"
						font.weight: Font.Bold
						font.pointSize: 30

						text: "KHG Mensa"
					}

					ListView {
						id: khg_mensa_menu

						Layout.fillWidth: true
						Layout.fillHeight: true

						spacing: 20

						model: khg_mensa

						delegate: Rectangle {
							anchors.left: parent.left
							anchors.right: parent.right
							anchors.leftMargin: 20
							anchors.rightMargin: 20

							height: (khg_mensa_menu.height - (khg_mensa_menu.count*20)) / khg_mensa_menu.count

							radius: 20
							color: "#ffffff"

							Text {
								anchors.fill: parent
								clip: true
								verticalAlignment: Text.AlignVCenter
								wrapMode: Text.WordWrap
								padding: 30
								color: "#000000"
								font.pointSize: 20
								text: display
							}
						}
					}
				}
			}
		}
	}
}

