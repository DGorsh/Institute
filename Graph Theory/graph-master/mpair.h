#ifndef MPAIR_H
#define MPAIR_H

template <typename K, typename V>
class MPair
{
public:

    K key;
    V value;

    MPair() {
    }

    MPair(const K& key, const V& value) : key(key), value(value){
    }

    K getKey() const {
        return key;
    }

    void setKey(const K &value) {
        key = value;
    }

    V getValue() const {
        return value;
    }

    void setValue(const V& value) {
        this->value = value;
    }

    bool operator > (const MPair<K,V>& with) const {
        return key > with.key;
    }

    bool operator < (const MPair<K,V>& with) const {
        return key < with.key;
    }

    bool operator >= (const MPair<K,V>& with) const {
        return key >= with.key;
    }

    bool operator <= (const MPair<K,V>& with) const {
        return key <= with.key;
    }

    bool operator == (const MPair<K,V>& with)  const{
        return key == with.key;
    }

};

#endif // MPAIR_H
