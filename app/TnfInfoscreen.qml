import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 6.0
import QtQuick.Shapes 1.10

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
				required property string lineColor
				required property string direction
				required property bool cancelled
				required property bool realtime
				required property var time

				required property int row

				height: 100
				anchors.left: parent.left
				anchors.right: parent.right

				color: row % 2 == 0 ? "#ffffff" : "#efefef"

				RowLayout {
					anchors.fill: parent

					Item {
						Layout.fillHeight: true
						Layout.preferredWidth: 130
						Rectangle {
							anchors.fill: parent
							anchors.topMargin: 10
							anchors.bottomMargin: 10
							anchors.leftMargin: 10

							color: lineColor

							radius: 20

							Text {
								anchors.fill: parent
								color: '#ffffff'
								text: line
								padding: 10
								font.pointSize: 40
								verticalAlignment: Text.AlignVCenter
								horizontalAlignment: Text.AlignHCenter
							}
						}
					}

					Text {
						Layout.fillWidth: true
						Layout.fillHeight: true

						elide: Text.ElideRight

						text: direction
						padding: 10
						font.pointSize: 40
						font.strikeout: cancelled
						verticalAlignment: Text.AlignVCenter
						horizontalAlignment: Text.AlignLeft
					}

					Text {
						Layout.fillHeight: true
						text: time.getTime() - root.time.time.getTime() < 60*60*1000 ?
							Math.floor((time.getTime() - root.time.time.getTime()) / 1000 / 60) :
							time.toLocaleTimeString(Qt.locale("de-AT"), Locale.ShortFormat)
						padding: 10
						font.pointSize: 40
						font.strikeout: cancelled
						verticalAlignment: Text.AlignVCenter
						horizontalAlignment: Text.AlignRight

						Shape {
							anchors.top: parent.top
							anchors.right: parent.right
							width: 30
							height: 30

							visible: realtime

							ShapePath {
								fillColor: "#00d000"
								strokeWidth: -1
								startX: 0; startY: 0
								PathLine { x: 30; y: 30 }
								PathLine { x: 30; y: 0 }
							}
						}
					}
				}
			}
		}
		
		StackLayout {
			Layout.fillHeight: true
			Layout.fillWidth: true

			Timer {
				interval: 10000; running: true; repeat: true
				onTriggered: parent.currentIndex = (parent.currentIndex + 1) % parent.count
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

			Rectangle {
				Layout.fillWidth: true
				Layout.fillHeight: true

				color: "#000000"

				StackLayout.onIsCurrentItemChanged: {
					if (StackLayout.isCurrentItem) {
						const teletext_page = teletext.pages[Math.floor(Math.random()*teletext.pages.length)];
						teletext.source = "https://appmeta.orf.at/teletext/orf1/"+teletext_page+"_0001.png";
					}
				}

				Image {
					id: teletext

					property var pages: [
						101, // Topstory Politik
						102, // Topstory Chronik
						103, // Topstory Leute
						104, // Topstory Wirtschaft
						105, // Topstory Sport
						107, // Topstory Show
						108, // Topstory Multimedia
						110, // Topstory Kultur
						113, // News Österreich + EU
						114,
						115,
						116,
						117,
						118,
						119,
						120,
						121,
						122,
						123,
						124,
						125,
						127, // News International
						128,
						129,
						130,
						131,
						132,
						133,
						134,
						136, // Chronik
						137,
						138,
						139,
						140,
						141,
						142,
						143,
						144,
						146, // Leute
						147,
						148,
						149,
						191, // News Kultur
						192,
						193, // News Show
						194,
						195,
					];

					onStatusChanged: {
						if (teletext.status == Image.Error) {
							const teletext_page = teletext.pages[Math.floor(Math.random()*teletext.pages.length)];
							teletext.source = "https://appmeta.orf.at/teletext/orf1/"+teletext_page+"_0001.png";
						}
					}

					anchors.fill: parent
					anchors.leftMargin: Math.floor(height / 69)

					cache: false
					sourceSize.width: 720
					sourceSize.height: 432
					sourceClipRect: Qt.rect(18, 0, 702, 414)
					smooth: false
				}
			}
		}
	}
}

