// Посетитель (Visitor)

#include <iostream>
#include <memory>
#include <vector>

#include <cassert>


namespace problem {

    class IDrawPrimitive {
    public:
        virtual ~IDrawPrimitive() = default;

        virtual void draw() const = 0;
    };

    class UIForm
    {
    public:
        void draw()
        {
            for(const auto & prim : mPrimitives)
            {
                prim->draw();
            }
        }
        
    private:
        std::vector<class IDrawPrimitive*> mPrimitives;
    };

    class Point : public IDrawPrimitive {
    public:
        Point(int x, int y)
            : m_x{x}, m_y{y}
        { }
        ~Point() = default;

        void draw() const override {
            std::cout << "Point::draw" << std::endl;
        }

        int getX() const { return m_x; }
        int getY() const { return m_y; }
    private:
        int m_x;
        int m_y;
    };

    class Line : public IDrawPrimitive {
    public:
        Line(const Point& p1, const Point& p2)
            : m_p1{p1}, m_p2{p2}
        { }
        ~Line() = default;

        void draw() const override {
            std::cout << "Line::draw" << std::endl;
        }

        Point getP1() const { return m_p1; }
        Point getP2() const { return m_p2; }
    private:
        Point m_p1;
        Point m_p2;
    };

    class Box : public IDrawPrimitive {
    public:
        Box(const Point& topLeft, const Point& bottomRight)
            : m_topLeft{topLeft},
              m_bottomRight{bottomRight}
        { }
        ~Box() = default;

        void draw() const override {
            std::cout << "Box::draw" << std::endl;
        }

        Point getTopLeft() const { return m_topLeft; }
        Point getBottomRight() const { return m_bottomRight; }
    private:
        Point m_topLeft;
        Point m_bottomRight;
    };

    class Circle : public IDrawPrimitive {
    public:
        Circle(const Point& center, int radius)
            : m_center{center},
              m_radius{radius}
        { }
        ~Circle() = default;

        void draw() const override {
            std::cout << "Circle::draw" << std::endl;
        }

        Point getCenter() const { return m_center; };
        int getRadius() const { return m_radius; }
    private:
        Point m_center;
        int m_radius;
    };

    class IDrawPrimitiveSerializer {
    public:
        virtual void serialize(IDrawPrimitive* primitive) = 0;
    };

    class ConsoleSerializer : public IDrawPrimitiveSerializer {
    public:
        ConsoleSerializer() = default;
        ~ConsoleSerializer() = default; 

        void serialize(IDrawPrimitive* primitive) {
            if (auto point = dynamic_cast<Point*>(primitive)) {
                serialize(*point);
                std::cout << std::endl;
            }
            else if (auto box = dynamic_cast<Box*>(primitive)) {
                serialize(*box);
                std::cout << std::endl;
            }
            else if (auto circle = dynamic_cast<Circle*>(primitive)) {
                serialize(*circle);
                std::cout << std::endl;
            }
            else {
                throw std::logic_error{"Unknown DrawPrimitive type detected!"};
            }
        }
    private:
        void serialize(const Point& point) {
            std::cout << "Point: x = " << point.getX() << " y = " << point.getY();
        }

        void serialize(const Box& box) {
            std::cout << "Box:\n\ttopLeft: ";
            serialize(box.getTopLeft());
            std::cout << "\n\tbottomRight: ";
            serialize(box.getBottomRight());
        }

        void serialize(const Circle& circle) {
            std::cout << "Circle:\n\tcenter: ";
            serialize(circle.getCenter());
            std::cout << "\n\tradius: " << circle.getRadius();
        }
    };


    void example() {
        std::cout << "problem::example" << std::endl;

        std::vector<std::unique_ptr<IDrawPrimitive>> primitives;
        primitives.emplace_back(
            std::make_unique<Point>(
                42,
                42
            )
        );
        // Oooops... 
        primitives.emplace_back(
            std::make_unique<Line>(
                Point{10, 10},
                Point{22, 22}
            )
        );
        primitives.emplace_back(
            std::make_unique<Box>(
                Point{0, 0},
                Point{10, 10}
            )
        );
        primitives.emplace_back(
            std::make_unique<Circle>(
                Point{42, 42},
                30
            )
        );

        std::unique_ptr<IDrawPrimitiveSerializer> serializer = 
            std::make_unique<ConsoleSerializer>();

        try {

            for (const auto& primitive : primitives)
                serializer->serialize(primitive.get());

        } catch(const std::exception& ex) {
            std::cout << "\t!!!Exception: " << ex.what() << std::endl;
        }

        std::cout << std::endl << std::endl;
    }
}


namespace pattern {

    class Point;
    class Box;
    class Circle;

    // Something new...
    class IDrawPrimitiveVisitor {
    public:
        virtual void visit(const Point * point) = 0;
        virtual void visit(const Box* box) = 0;
    };

/*****************************************************************************
 *          DrawPrimitive
*****************************************************************************/
    class IDrawPrimitive {
    public:
        // As in the previous example
        virtual void draw() const = 0;
        // Something new... 
        virtual void accept(IDrawPrimitiveVisitor * visitor) const = 0;
    };

    class Point : public IDrawPrimitive {
    public:
        Point(int x, int y)
            : m_x{x}, m_y{y}
        { }

        void draw() const override {
            std::cout << "Point::draw" << std::endl;
        }

        void accept(IDrawPrimitiveVisitor* visitor) const override {
            visitor->visit(this);
        }

        int getX() const { return m_x; }
        int getY() const { return m_y; }
    private:
        int m_x;
        int m_y;
    };

    class Box : public IDrawPrimitive {
    public:
        Box(const Point& topLeft, const Point& bottomRight)
            : m_topLeft{topLeft},
              m_bottomRight{bottomRight}
        { }
        ~Box() = default;

        void draw() const override {
            std::cout << "Box::draw" << std::endl;
        }

        void accept(IDrawPrimitiveVisitor* visitor) const override {
            visitor->visit(this);
        }

        Point getTopLeft() const { return m_topLeft; }
        Point getBottomRight() const { return m_bottomRight; }
    private:
        Point m_topLeft;
        Point m_bottomRight;
    };

    class Circle : public IDrawPrimitive {
    public:
        Circle(const Point& center, int radius)
            : m_center{center},
              m_radius{radius}
        { }
        ~Circle() = default;

        void draw() const override {
            std::cout << "Circle::draw" << std::endl;
        }
        
        Point getCenter() const { return m_center; };
        int getRadius() const { return m_radius; }
    private:
        Point m_center;
        int m_radius;
    };


/*****************************************************************************
 *          Serializersb
*****************************************************************************/

    class JsonSerializer : public IDrawPrimitiveVisitor {
    public:
        JsonSerializer(std::ostream& out)
            : m_out{out} {
        }

        void visit(const Point * point) override {
            assert(point);

            m_out << "\"Point\": ";
            serialize(*point);
            m_out << std::endl;
        }

        void visit(const Box* box) override {
            assert(box);

            m_out << "\"Box\": ";
            serialize(*box);
            m_out << std::endl;
        }
    private:
        void serialize(const Point& point) {
            m_out << "{ \"x\": " << point.getX() << ", \"y\": " << point.getY() << " }";
        }

        void serialize(const Box& box) {
            m_out << "{ ";
            m_out << "\"TopLeft\": ";
            serialize(box.getTopLeft());
            m_out << ", \"BottomRight\": ";
            serialize(box.getBottomRight());
            m_out << " }";
        }

        std::ostream& m_out;
    };

    class XmlSerializer : public IDrawPrimitiveVisitor {
    public:
        XmlSerializer(std::ostream& out)
            : m_out{out}
        {}

        void visit(const Point * point) override {
            assert(point);

            m_out << "<Point> ";
            serialize(*point);
            m_out << " </Point>";
            m_out << std::endl;
        }

        void visit(const Box* box) override {
            assert(box);

            m_out << "<Box> ";
            serialize(*box);
            m_out << " </Box>";
            m_out << std::endl;
        }

    private:
        void serialize(const Point& point) {
            m_out << "<x>" << point.getX() << "</x>";
            m_out << "<y>" << point.getY() << "</y>";
        }

        void serialize(const Box& box) {
            m_out << "<TopLeft> ";
            serialize(box.getTopLeft());
            m_out << " </TopLeft> ";
            m_out << "<BottomRight> ";
            serialize(box.getBottomRight());
            m_out << " </BottomRight> ";
        }

        std::ostream& m_out;
    };

    void example() {
        std::cout << "pattern::example" << std::endl;

        std::vector<std::unique_ptr<IDrawPrimitive>> primitives;
        primitives.emplace_back(
            std::make_unique<Point>(
                42,
                42
            )
        );
        primitives.emplace_back(
            std::make_unique<Box>(
                Point{0, 0},
                Point{10, 10}
            )
        );
//         primitives.emplace_back(
//             std::make_unique<Circle>(
//                 Point{42, 42},
//                 30
//             )
//         );

        std::unique_ptr<IDrawPrimitiveVisitor> serializer1 = 
            std::make_unique<JsonSerializer>(std::cout);

        std::unique_ptr<IDrawPrimitiveVisitor> serializer2 = 
            std::make_unique<XmlSerializer>(std::cout);

        std::cout << "Serialize into JSON format:" << std::endl;
        for (const auto& primitive : primitives)
            primitive->accept(serializer1.get());


        std::cout << "Serialize into XML format:" << std::endl;
        for (const auto& primitive : primitives)
            primitive->accept(serializer2.get());

        std::cout << std::endl << std::endl;
    }
}

int main(int, char *[]) {

    problem::example();
    
    std::cout<< "###############" << std::endl;
    
    pattern::example();

    return 0;
}
