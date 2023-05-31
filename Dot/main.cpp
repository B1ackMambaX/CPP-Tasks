#include <iostream>
#include "Vector.h"
#include "limits"
#include "algorithm"

double calculateTime(Line dir, Plane cubeFace) {
    double time = -(cubeFace.d + cubeFace.a * dir.p.x + cubeFace.b * dir.p.y + cubeFace.c * dir.p.z) /
                  (cubeFace.a * dir.v.x + cubeFace.b * dir.v.y + cubeFace.c * dir.v.z);
    if (time > 0) return time;
    return numeric_limits<int>::max();
}

int main() {
    Point pos;
    Vector speed;
    double time;
    int bounceCounter = 0;

    cout << "Enter start pos: ";
    cin >> pos.x >> pos.y >> pos.z;
    cout << "Enter speed vector: ";
    cin >> speed.x >> speed.y >> speed.z;
    cout << "Enter time: ";
    cin >> time;

    while (time >= 0) {
        Line dir = Line(pos, speed);
        double times[] = {calculateTime(dir, Plane(1, 0, 0, 0)), calculateTime(dir, Plane(0, 1, 0, 0)),
                          calculateTime(dir, Plane(0, 0, 1, 0)), calculateTime(dir, Plane(1, 0, 0, -1)),
                          calculateTime(dir, Plane(0, 1, 0, -1)), calculateTime(dir, Plane(0, 0, 1, -1))};

        double bounceTime = *min_element(times, times + 6);
        Plane bouncePlane = Plane(0, 0, 0, 0);
        for(int i = 0; i < 6; ++i) {
            if(times[i] == bounceTime) {
                if (i == 0 || i == 3)
                    bouncePlane.a = 1;
                else if (i == 1 || i == 4)
                    bouncePlane.b = 1;
                else if (i == 2 || i == 5)
                    bouncePlane.c = 1;
            }
        }
        if(time - bounceTime < 0) {
            pos = Point(dir.p.x + speed.x, dir.p.y + speed.y, dir.p.z + speed.z);
            cout << "Final pos: " << pos.x << " " << pos.y << " " << pos.z << endl;
            break;
        }
        Vector normal(bouncePlane.a, bouncePlane.b, bouncePlane.c);
        Vector projection = speed - normal * ((speed * normal) / (normal * normal));
        speed = projection * 2 - speed;
        time -= bounceTime;
        pos = Point(dir.p.x + dir.v.x * bounceTime, dir.p.y + dir.v.y * bounceTime, dir.p.z + dir.v.z * bounceTime);
        cout << "Bounce pos: " << pos.x << " " << pos.y << " " << pos.z << endl;
        bounceCounter++;
    }
    cout << "Bounce counter: " << bounceCounter << endl;
    return 0;
}
