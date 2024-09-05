from PyQt6.QtWidgets import QWidget

class BoardWindow(QWidget):
    
    def __init__(self, app):
        super().__init__()
        self.app = app

        self.setWindowTitle("Board")

        self.setGeometry(300, 300, 600, 400)
        self.setStyleSheet("background-color: #161616")