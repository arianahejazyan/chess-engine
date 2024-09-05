import sys
from PyQt6.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QTextEdit, QLineEdit, QWidget, QLabel
from PyQt6.QtGui import QFont, QFontDatabase
from PyQt6.QtCore import Qt

class Interpreter:
    def process_command(self, command: str):
        # Your custom command processing logic goes here
        return f"Processed: {command}"


class TerminalWindow(QWidget):
    def __init__(self, app, parent=None):
        super().__init__(parent)
        self.app= app

        self.setWindowTitle("Talia Terminal")
        self.setGeometry(800, 400, 600, 400)
        self.setStyleSheet("background-color: #161616")
        self.setMinimumWidth(400)
        self.setMinimumHeight(300)

        font_id = QFontDatabase.addApplicationFont("/external/Projects/chess-engine/talia/assets/font/Fira_Code_v6.2/ttf/FiraCode-Regular.ttf")
        if font_id == -1:
            print("Font could not be loaded.")
        else:
            font_family = QFontDatabase.applicationFontFamilies(font_id)[0]
            custom_font = QFont(font_family, 12)

        # Output area for displaying results
        self.output = QTextEdit(self)
        self.output.setReadOnly(True)
        self.output.setFont(custom_font)
        self.output.setStyleSheet("""
            QTextEdit {
                color: #FFD700;
                background-color: #161616;
                border: None;
                padding: 5px;
            }

            QScrollBar:vertical {
                border: none;
                background: none;
                width: 10px;
            }

            QScrollBar::handle:vertical {
                background: #B0B0B0;
                border-radius: 5px;
                min-height: 20px;
            }

            QScrollBar::add-line:vertical,
            QScrollBar::sub-line:vertical,
            QScrollBar::up-arrow:vertical,
            QScrollBar::down-arrow:vertical,
            QScrollBar::add-page:vertical,
            QScrollBar::sub-page:vertical {
                background: #161616;
                border: none;
                width: 0px;
                height: 0px;
            }
        """)

        # Set styled text with HTML, including alternative Unicode check marks
        styled_text = (
            "<span style='color: #32CD32;'>✔</span> Success <br/>"
            "<span style='color: red;'>✘</span> Error"
        )
        self.output.setHtml(styled_text)

        # Input area for user commands
        self.input = QLineEdit(self)
        self.input.setFont(custom_font)
        self.input.setStyleSheet("""
            QLineEdit {
                color: #FFFFFF;
                background-color: #161616;
                border: None;
                padding: 5px;
            }
        """)
        self.input.setText("> ")
        self.input.returnPressed.connect(self.execute_command)

        # Layout to arrange the input and output widgets
        layout = QVBoxLayout()
        layout.addWidget(self.input)
        layout.addWidget(self.output)
        self.setLayout(layout)

        # Ensure '>' remains at the start
        self.input.textEdited.connect(self.enforce_prefix)

    def enforce_prefix(self):
        text = self.input.text()
        if not text.startswith("> "):
            self.input.setText("> " + text.lstrip("> "))
            self.input.setCursorPosition(len(self.input.text()))  # Move cursor to the end

    def execute_command(self):
        command = self.input.text().strip()
        if command:
            # Remove the '>' prefix for command processing
            command = command[1:].strip()
            self.output.append(f'<span style="color:#FFFFFF;">build</span> <span style="color:#00BFFF;">project</span>')
            result = self.app.interpreter.process_command(command)
            print(result)
            self.output.append(f"<span style='color: #B0B0B0;'>build project</span>")
        self.input.clear()
        self.input.setText("> ")  # Reset the input field with '>'
