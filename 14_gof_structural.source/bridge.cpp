// Мост (Bridge)

#include <iostream>
#include <memory>

// bad
struct IShape {
    virtual void show() = 0;
    virtual ~IShape() = default;
};


struct Square : IShape {
    void show() override {
        std::cout << "Square show!" << std::endl;
    }
};

struct Circle : Square {
    void show() override {
        std::cout << "Circle show!" << std::endl;
    }
};

struct Triangle : Square {
    void show() override {
        std::cout << "Triangle show!" << std::endl;
    }
};


struct BlackSquare : Square {
    void show() override {
        std::cout << "Black Square show!" << std::endl;
    }
};

struct BlueSquare : Square {
    void show() override {
        std::cout << "Blue Square show!" << std::endl;
    }
};

struct RedSquare : Square {
    void show() override {
        std::cout << "Red Square show!" << std::endl;
    }
};

// no bad
struct IColor {
    virtual void color() = 0;
    virtual ~IColor() = default;
};

struct Black : IColor {
    void color() override {
        std::cout << "Black";
    }
};

struct Red : IColor {
    void color() override {
        std::cout << "Red";
    }
};

struct SquareWithBrige : public Square {
    SquareWithBrige(std::unique_ptr<IColor> color) 
        : m_color{std::move(color)} {

        }

    void show() override {
        m_color->color();
        std::cout << " Square show!" << std::endl;
    }
private:
    std::unique_ptr<IColor> m_color;
};


void testShapes() {

    BlackSquare blackSquare;
    blackSquare.show();

    SquareWithBrige squareWithBrige( std::make_unique<Black>() );
    squareWithBrige.show();
}


struct ClockSignal {
    virtual void now() = 0;
};

struct InternetClockSignal : public ClockSignal {
    void now() override {
        std::cout << "internet clock" << std::endl;
    }
};

struct LocalClockSignal : public ClockSignal {
    void now() override {
        std::cout << "local clock" << std::endl;
    }
};

struct Clock {
    ClockSignal *s = nullptr;
    void refresh()
    {
        s->now();
        display();
    }
    virtual void display() = 0;
    virtual ~Clock() {
        delete s;
    }
};

struct DigitalClock : public Clock {
    void display() {
        std::cout << "digital" << std::endl;
    }
};

struct AnalogClock : public Clock {
    void display() {
        std::cout << "analog" << std::endl;
    }
};


void testClock() {
    auto c = std::unique_ptr<Clock>(new DigitalClock);
    c->s = new InternetClockSignal;

    c->refresh();
}


int main(int, char *[]) {

    testShapes();
    testClock();

    return 0;

}
