#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.hpp"
#include <vector>
#include <memory>

using std::make_shared;
using std::shared_ptr;
using std::vector;

class Hittable_list : public Hittable
{
private:
    vector<shared_ptr<Hittable>> objects;

public:
    Hittable_list() {}
    Hittable_list(shared_ptr<Hittable> obj) { add(obj); }

    void add(shared_ptr<Hittable> obj) { objects.push_back(obj); }
    void clear() { objects.clear(); }

    virtual bool hit(const Ray &r, double t_min, double t_max, hit_record &hrec) const override;
};

bool Hittable_list::hit(const Ray &r, double t_min, double t_max, hit_record &hrec) const
{
    hit_record temphrec;
    bool hit_something = false;
    double closest_t = t_max;

    for (const auto obj : objects)
    {
        if (obj->hit(r, t_min, closest_t, temphrec))
        {
            hit_something = true;
            closest_t = temphrec.t;
            hrec = temphrec;
        }
    }
    return hit_something;
}

#endif // !HITTABLE_LIST_H