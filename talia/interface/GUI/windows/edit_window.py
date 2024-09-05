from PyQt6.QtWidgets import QWidget

class EditWindow(QWidget):
    
    def __init__(self, app):
        super().__init__()
        self.app = app

        self.setWindowTitle("Edit")