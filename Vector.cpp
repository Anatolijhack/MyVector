#include <iostream>
#include <algorithm>
template <typename T>
class MyVector
{
private:
	T* data = nullptr;
	int size = 0;
	int capacity = 0;
	void resize(size_t cap)
	{
		//обьект T  = приобразование к T(оператор выделения памяти(размер обьекта T + cap)
		T* new_data = static_cast<T*>(operator new(sizeof(T) * cap));
		for (size_t i = 0; i < size; i++)
		{
			new(new_data + i) T(std::move(data[i]));
			data[i].~T();
		}
		operator delete(data);
		data = new_data;
		capacity = cap;
	}
	void reserve(size_t new_cap)
	{
		if (new_cap <= capacity)
			return;

		// выделяем сырую память
		T* new_data = static_cast<T*>(operator new(sizeof(T) * new_cap));

		// переносим элементы (move)
		for (size_t i = 0; i < size; i++)
		{
			new (new_data + i) T(std::move(data[i]));
			data[i].~T();
		}

		// освобождаем старую память
		operator delete(data);

		data = new_data;
		capacity = new_cap;
	}
public:
	MyVector()
	{
		this->size = 0;
		this->capacity = 0;
		this->data = nullptr;
	}
	~MyVector()
	{
		//цикл прохода по вектору
		for (int i = 0; i < size; i++)
		{
			//Ручное удаление T обьекта
			data[i].~T();

		}
		//Удаление  выделеной памяти
		operator delete(data);
	}
	MyVector(const MyVector& other)
	{
		size = other.size;
		capacity = other.capacity;

		data = static_cast<T*>(operator new(sizeof(T) * capacity));

		for (size_t i = 0; i < size; i++)
		{
			new (data + i) T(other.data[i]);
		}
	}
	MyVector(MyVector&& other)
	{
		data = other.data;
		size = other.size;
		capacity = other.capacity;

		other.data = nullptr;
		other.size = 0;
		other.capacity = 0;
	}
	MyVector& operator=(const MyVector& other)
	{
		if (this == &other)
			return *this;

		// уничтожаем старые элементы
		for (size_t i = 0; i < size; ++i)
			data[i].~T();

		operator delete(data);

		size = other.size;
		capacity = other.capacity;

		data = static_cast<T*>(operator new(sizeof(T) * capacity));

		for (size_t i = 0; i < size; ++i)
		{
			new (data + i) T(other.data[i]);
		}

		return *this;
	}
	MyVector& operator=(MyVector&& other)
	{
		if (this == &other)
			return *this;

		// удаляем свои данные
		for (size_t i = 0; i < size; ++i)
			data[i].~T();

		operator delete(data);

		// забираем ресурсы у other
		data = other.data;
		size = other.size;
		capacity = other.capacity;

		// обнуляем other
		other.data = nullptr;
		other.size = 0;
		other.capacity = 0;

		return *this;
	}
	class Iterator
	{
	public:
		T* ptr;
		Iterator(T* node)
		{
			this->ptr = node;
		}
		Iterator& operator++()
		{
			ptr++;
			return *this;
		}
		T& operator*()
		{
			return *ptr;
		}
		bool operator!=(const Iterator& other)
		{
			return ptr != other.ptr;
		}
	};
	Iterator begin()
	{
		return Iterator(data);
	}
	Iterator end()
	{
		return Iterator(data + size);
	}
	class ConstIterator
	{
	public:
		const T* ptr;
		ConstIterator(T* node)
		{
			this->ptr = node;
		}
		ConstIterator& operator++()
		{
			ptr++;
			return *this;
		}
		const T& operator*() const
		{
			return *ptr;
		}
		bool operator!=(const ConstIterator& other) const
		{
			return ptr != other.ptr;
		}
	};
	ConstIterator begin()
	{
		return ConstIterator(data);
	}
	ConstIterator end()
	{
		return ConstIterator(data + size);
	}
	void push_front(T value)
	{
		if (size == capacity)
		{
			resize(capacity == 0 ? 1 : capacity * 2);
		}

		for (int i = size; i > 0; i--)
		{
			//cоздаем следующий обьект data присваивая ему значение предыдущего
			new (data + i) T(std::move(data[i - 1]));
			//предыдущий удаляем
			data[i - 1].~T();
		}
		//В начало добавляем наше значение
		new (data) T(std::move(value));
		//Увеличиваем размер
		size++;
	}
	void pop_front()
	{
		if (size == 0) return;
		//Удаление T обьекта в начале
		data[0].~T();

		for (int i = 1; i < size; i++)
		{
			//создаем обьект в памяти присваиваем ему  текущее значение
			new (data + i - 1) T(std::move(data[i]));
			//удаляем текщее значение не указатель
			data[i].~T();
		}
		//cнимаем size
		size--;
	}
	void push_back(T value)
	{
		resize(capacity == 0 ? 1 : capacity * 2);
		//адрес последнего элемента  присваиваем T обьект
		new(data + size) T(value);
		size++;
	}
	void pop_back()
	{
		//Убираем последний єлемент и удаляем T обьект
		data[size - 1].~T();
		size--;
	}
void DeletePeriod(int index, int index2)
{
    int count = index2 - index;

    for (int i = index; i < index2; i++)
        data[i].~T();

    for (int i = index2; i < size; i++)
    {
        new(data + i - count) T(std::move(data[i]));
        data[i].~T();
    }

    size -= count;
}
	void Swap(int index, int index2)
	{
		std::swap(data[index], data[index2]);
	}

	void insert(size_t index, const T& value)
	{
		if (index > size) return;


		if (size == capacity)
			resize(capacity == 0 ? 1 : capacity * 2);

		// сдвиг вправо
		for (size_t i = size; i > index; --i)
		{
			new (data + i) T(std::move(data[i - 1]));
			data[i - 1].~T();
		}

		new (data + index) T(value);
		size++;
	}
	template <typename InputIt>
	void insert(size_t pos, InputIt first, InputIt last) {
		size_t count = std::distance(first, last);

		if (count == 0) return;

		// 1. проверка capacity
		if (size + count > capacity)
		{
			size_t new_cap = std::max(capacity * 2, size + count);
			resize(new_cap);
		}

		// 2. двигаем существующие элементы вправо
		for (size_t i = size; i > pos; --i) {
			new (data + i + count - 1) T(std::move(data[i - 1]));
			data[i - 1].~T();
		}

		// 3. вставляем новые элементы
		size_t i = pos;
		for (auto it = first; it != last; ++it, ++i) {
			new (data + i) T(*it);
		}

		// 4. обновляем size
		size += count;
	}
	void erase(size_t index)
	{
		if (index >= size) return;

		for (size_t i = index; i < size - 1; ++i)
		{
			new (data + i) T(std::move(data[i + 1]));
			data[i + 1].~T();
		}

		size--;
	}
	template<typename ...Args>
	void emplace_back(Args&&... args)
	{
		if (size == capacity)
			resize(capacity == 0 ? 1 : capacity * 2);

		new(data + size) T(std::forward<Args>(args)...);
		size++;

	}
	template<typename ...Args>
	void emaplace(int index, Args&&... args)
	{
		if (size == capacity)
			resize(capacity == 0 ? 1 : capacity * 2);
		for (int i = size; i > index; i++)
		{
			new(data + i) T(std::move(data[i - 1]));
			data[i - 1].~T();
		}
		new(data + index) T(std::forward<Args>(args)...);
		size++;
	}
	void assign(int count, T value)
	{
		if (count > capacity)
			reserve(count);

		clear();
		for (int i = 0; i < count; i++)
		{
			new(data + i) T(value);
		}
		size = count;
	}
	void insert(int index, int count, const T& value)
	{

		// сдвиг вправо
		for (int i = size - 1; i >= index; --i)
		{
			new (data + i + count) T(std::move(data[i]));
			data[i].~T();
		}

		// вставка новых элементов
		for (int i = 0; i < count; ++i)
		{
			new (data + index + i) T(value);
		}

		size += count;
	}
	template<typename InputIt>
	void assign(InputIt first, InputIt last)
	{
		int count = std::distance(first, last);

		// если не хватает памяти
		if (count > capacity)
			reserve(count);


		// уничтожаем старые
		clear();

		int i = 0;
		for (auto it = first; it != last; ++it, ++i)
		{
			new (data + i) T(*it);
		}

		size = count;
	}
	T& operator[](int index)
	{
		return data[index];
	}
	const T& operator[](int index)
	{
		return data[index];
	}
	bool empty() const
	{
		return size == 0;
	}
	T& at(int i) const
	{
		return data[i];
	}
	T& front() const
	{
		return data[0];
	}
	T& back() const
	{
		return data[size - 1];
	}
	T* Getdata() const
	{
		return data;
	}
	void clear()
	{
		for (int i = 0; i < size; i++)
		{
			data[i].~T();
		}
		size = 0;
	}
};
int main()
{

}
