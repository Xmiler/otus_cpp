// Фасад (Facade)

#include <iostream>

struct VideoControl {
    void info() {};
    void alert() {};
};

struct Database {
    void create() {};
    void update() {};
};

struct Printer {
    void print() {};
};

struct Fiscal {
    void report() {};
};

struct Facade {
    VideoControl vc;
    Database db;
    Printer printer;
    Fiscal f;

    void sale_doc() {
        db.create();
        vc.info();
        printer.print();
        f.report();
    }
    
    void ret_doc() {
        db.update();
        vc.alert();
        printer.print();
        f.report();
    }
};

int main(int, char *[]) {
    Facade r;

    r.sale_doc();
    r.ret_doc();

    return 0;
}
