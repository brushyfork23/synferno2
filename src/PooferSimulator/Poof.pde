
class Poof {
  final int HEIGHT_GROWTH = 150; // Speed at which fire ball grows vertically
  final int WIDTH_GROWTH = 100; // Speed at which fire ball grows horizontally
  final int HEIGHT_SHRINK = 60; // Speed at which fireball shrinks veritcally
  final int WIDTH_SHRINK = 10; // Speed at which fireball shrinks horizontally
  final int CLIMB = 150; // Speed at which fireball rises after solenoid is disabled
  
  
  int w=0;
  int h=0;
  int bottom=0;
  int column;
  int maxAttainedWidth=0;
  int maxAttainedHeight=0;
  boolean growing = false;
  
  
  Poof(int column){
    this.column = column;
  }
  
  void setGrowing(boolean isGrowing) {
    this.growing = isGrowing;
  }
  
  void animate() {
    if (this.growing) {
      grow();
    } else {
      decay();
    }
    
    int x = this.column * width / 4 + width/8;
    int y = height - this.bottom - (this.h/2);
    ellipse(x, y, this.w, this.h);
  }
  
  void grow() {
    if (this.w < 3 * width / 16) { // 3/4 * width/4
      this.w += WIDTH_GROWTH;
      this.maxAttainedWidth = this.w;
    }
    if (this.h < height*2) {
      this.h += HEIGHT_GROWTH;
      this.maxAttainedHeight = this.h;
    }
  }
  
  void decay() {
    if (bottom < height + h){
      this.bottom += CLIMB;
    }
    if (this.w > (this.maxAttainedWidth * 7 / 10)) {
      this.w -= WIDTH_SHRINK;
    }
    if (this.h > (this.maxAttainedHeight * 1 / 5)) {
      this.h -= HEIGHT_SHRINK;
    }
  }
}
