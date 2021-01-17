// Приспособленец (Flyweight)

#include <iostream>
#include <map>

struct ImageView;

struct Image {
    Image crop(int x1, int y1, int x2, int y2) {};
    void show() {};
};




struct ImageView {
    ImageView(int x, int y, int width, int height, const Image& image)
        : m_image{image}
        , m_height{height}
        , m_width{width} {

    }

    void show() const {
        // show only m_width x m_height rect.
    }
private:
    const Image& m_image;
    const int m_width;
    const int m_height;
};

void testImageView() {
    Image veryBigImage;

    auto view1 = ImageView{100, 100, 10, 40, veryBigImage};
    view1.show();
    auto view2 = ImageView{500, 100, 1024, 780, veryBigImage};
    view2.show();
}


int main(int, char *[]) {
    testImageView();

    return 0;
}
