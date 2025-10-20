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

				text: root.time.time.toLocaleTimeString(Qt.locale("de-AT"), Locale.ShortFormat)
			}
		}
	}

	RowLayout {
		Layout.fillWidth: true
		Layout.fillHeight: true

		spacing: 0

		ListView {
			id: departures

			Layout.fillHeight: true
			Layout.fillWidth: true

			clip: true
			
			model: root.departures
			
			property var columnAlignments: [Text.AlignHCenter, Text.AlignLeft, Text.AlignRight]
			
			delegate: Rectangle {
				required property string line
				required property string direction
				required property var time

				required property int row

				height: 100
				width: parent.width

				color: row % 2 == 0 ? "#ffffff" : "#efefef"

				RowLayout {
					anchors.fill: parent

					Text {
						Layout.fillHeight: true
						Layout.preferredWidth: 120
						text: line
						padding: 10
						font.pointSize: 40
						verticalAlignment: Text.AlignVCenter
						horizontalAlignment: Text.AlignHCenter
					}

					Text {
						Layout.fillWidth: true
						Layout.fillHeight: true

						text: direction
						padding: 10
						font.pointSize: 40
						verticalAlignment: Text.AlignVCenter
						horizontalAlignment: Text.AlignLeft
					}

					Text {
						Layout.fillHeight: true
						Layout.preferredWidth: 120
						text: Math.floor((time.getTime() - root.time.time.getTime()) / 1000 / 60)
						padding: 10
						font.pointSize: 40
						verticalAlignment: Text.AlignVCenter
						horizontalAlignment: Text.AlignRight
					}
				}
			}
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

							height: children[0].implicitHeight

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

							height: children[0].implicitHeight

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

