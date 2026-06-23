#include <iostream>
template <typename V>
class MyVector
{
private:
	V* data;
	int size;
	int capacity;
	void reserve(int new_capacity)
	{
		if (new_capacity < capacity)
		{
			return;
		}
		V* new_data = (V*)(operator new(sizeof(V) * new_capacity));

		int i = 0;
		try
		{
			for (; i < size; i++)
			{
				new(new_data + i) V(std::move(data[i]));
			}
		}
		catch (...)
		{
			// откат
			for (int j = 0; j < i; j++)
				new_data[j].~V();

			operator delete(new_data);
			throw;
		}

		for (int i = 0; i < size; i++)
		{
			new(new_data + i) V(std::move(data[i]));
			data[i].~V();
		}
		operator delete(data);

		data = new_data;
		capacity = new_capacity;
	}
	void resize(int new_size)
	{
		if (new_size < size)
		{
			for (int i = new_size; i < size; i++)
			{
				data[i].~V();
			}
		}
		else if (new_size > size)
		{
			if (new_size > capacity)
			{
				reserve(capacity * 2);
			}
			for (int i = size; i < new_size; i++)
			{
				new(data + i) V();
			}
		}
		size = new_size;
	}
public:
	V& operator[](int index)
	{
		return data[index];
	}
	MyVector()
	{
		this->capacitydata = nullptr;
		this->size = 0;
		this->capacity = 0;
	}
	MyVector(const MyVector& other)
	{
		size = other.size;
		capacity = other.capacity;

		data = (V*)(operator new(sizeof(V) * capacity);
		for (int i = 0; i < size; i++)
		{
			new(data + i) V(other.data[i]);
		}
	}
	MyVector(MyVector&& other)
	{
		size = other.size;
		capacity = other.capacity;
		data = other.data;

		other.size = 0;
		other.capacity = 0;
		other.data = nullptr;
	}

	MyVector& operator=(const MyVector& other)
	{
		if (this == &other)
		{
			return *this;
		}
		clear();
		operator delete (data);

		data = (V*)(operator new(sizeof(V) * capacity);
		for (int i = 0; i < size; i++)
		{
			new(data + i) V(other.data[i]);
		}
	}
	MyVector& operator=(MyVector&& other)
	{
		if (this == &other)
		{
			return *this;
		}
		size = other.size;
		capacity = other.capacity;
		data = other.data;

		other.size = 0;
		other.capacity = 0;
		other.data = nullptr;

		return *this;
	}
	void clear()
	{
		for (int i = 0; i < size; i++)
		{
			data[i].~V();
		}
	}
	void push_back(V value)
	{
		if (capacity == size)
		{
			if (capacity != 0)
			{
				reserve(capacity * 2);
			}
			else
			{
				reserve(1);
			}
		}
		new(data + size) V(std::move(value));
		size++;
	}
	void push_front(V value)
	{
		if (capacity == size)
		{
			if (capacity != 0)
			{
				reserve(capacity * 2);
			}
			else
			{
				reserve(1);
			}
		}
		for (int i = size; i > 0; i--)
		{
			new(data + i) V(std::move(data[i - 1]));
			data[i - 1].~V();
		}
		size++;
	}
	void push_by_index(int index, V value)
	{

		if (index > size)
		{
			return;
		}
		if (capacity == size)
		{
			if (capacity != 0)
			{
				reserve(capacity * 2);
			}
			else
			{
				reserve(1);
			}
		}
		for (int i = size; i > index; i--)
		{
			new(data + i) V(std::move(data[i - 1]));
			data[i - 1].~V();
		}
		size++;
	}
	void pop_back()
	{
		data[size - 1].~V();
		size--;
	}
	void pop_front()
	{
		data[0].~V();
		for (int i = 0; i < size - 1; i++)
		{
			new(data + i) V(std::move(data[i + 1]));
			data[i].~V();
		}
	}
	void DeletePeriodA(int index, int index2)
	{
		int count = index2 - index;
		for (int i = index2; i < size; i++)
		{
			new(data + i - count) V(std::move(data[i]));
			data[i].~V();
		}
		for (int i = size - count; i < size; i++)
		{
			data[i].~V();
		}
		size -= count;
	}
	void DeletePeriodB(int index, int index2)
	{
		int count = index2 - index;
		int tail = size - index2;
		int moves = std::min(count, tail);
		for (int i = 0; i < moves; i++)
		{
			int to = size - i - 1;
			int from = index + i;

			data[to].~V();
			new(data + to) V(std::move(data[from]));
			data[from].~V();
		}
		for (int i = moves; i < count; i++)
		{
			data[index + i].~V();
		}
		size -= count;
	}
	V* find(V value)
	{
		for (int i = 0; i < size; i++)
		{
			if (data[i] == value)
			{
				return &data[i];
			}
		}
		return nullptr;
	}
	void insert_period(int index, V* first, V* second)
	{

		int count = std::distance(first, second);

		if (count + size > capacity)
		{
			size_t new_cap = std::max(capacity * 2, size + count);
			reserve(new_cap);
		}

		for (int i = size; i > index; i--)
		{
			new(data + i + count - 1) V(std::move(data[i - 1]));
			data[i - 1].~V();
		}
		for (int i = 0; i < count; i++)
		{
			new(data + i + index) V(first[i]);
		}
		size += count;
	}
	void shrink_to_fit()
	{
		if (size == capacity)
		{
			return;
		}
		if (size == 0)
		{
			operator delete(data);
			data = nullptr;
			size = 0;
			capacity = 0;
		}
		V* new_data = (V*)(operator new(sizeof(V) * size));
		for (int i = 0; i < size; i++)
		{
			new(new_data + i) V(std::move(data[i]));
			data[i].~V();
		}
		operator delete(data);
		capacity = new_data;

	}
	int operator-(const Iterator& other) const
	{
		return data - other.data;
	}
	template<typename... Args>
	void emplace_back(Args&&... args)
	{
		if (size == capacity)
		{
			reserve(capacity ? capacity * 2 : 1);
		}
		new(data + size) V(std::forward<Args>(args)...);
		size++;
	}
	template <typename ...Arg>
	void emplace_backs(int index, Arg&&... arg)
	{
		if (size == capacity)
		{
			reserve(capacity * 2);
		}
		for (int i = size; i > index; i--)
		{
			new(data + i)  V(std::move(data[i - 1]));
			data[i - 1].~T();
		}
		new(data + index) V(std::forward<Arg>(arg)...);

		size++;
	}
	class Iterator
	{

	public:
		V* ptr;
		Iterator(V* data)
		{
			this->ptr = data;
		}
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

		Iterator& operator++()
		{
			ptr++;
			return *this;
		}
		V* operator->() const { return ptr; }
        
		Iterator& operator*()
		{
			return *ptr;
		}
		Iterator operator+(int n) const
		{
			return Iterator(ptr + n);
		}
		Iterator operator-(int n) const
		{
			return Iterator(ptr - n);
		}
		Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }
		int operator-(const Iterator& other) const { return ptr - other.ptr; }
		Iterator& operator+=(int n) { ptr += n; return *this; }
		Iterator& operator-=(int n) { ptr -= n; return *this; }

		
		V& operator[](int n) const { return *(ptr + n); }

		Iterator& operator--()
		{
			data--;
			return *this;
		}
		bool operator==(const Iterator& other) const { return ptr == other.ptr; }
		bool operator!=(const Iterator& other) const { return ptr != other.ptr; }

		bool operator<(const Iterator& other) const { return ptr < other.ptr; }
		bool operator>(const Iterator& other) const { return ptr > other.ptr; }
		bool operator<=(const Iterator& other) const { return ptr <= other.ptr; }
		bool operator>=(const Iterator& other) const { return ptr >= other.ptr; }

		// доступ (нужно для insert/erase)
		V* get() const { return ptr; }
	};
	class ConstIterator
	{
	private:
		V* data;
	public:
		ConstIterator(V* data)
		{
			this->data = data;
		}
		const ConstIterator& operator*() const
		{
			return *data;
		}
		ConstIterator& operator++()
		{
			data++;
			return *this;
		}
		bool operator !=(const ConstIterator& other)
		{
			return data != other.data;
		}
	};
	Iterator insert(Iterator it, V& value)
	{
		int = it.data - data;

		if (size == capacity)
			reserve(capacity ? capacity * 2 : 1);

		for (int i = size; i > index; i--)
		{
			new (data + i) V(std::move(data[i - 1]));
			data[i - 1].~V();
		}
		new(data + index) V(value);
		size++;

		return Iterator(data + (index);
	}
	Iterator erase(Iterator it)
	{
		int index = it.data - data;
		data[index].~V();

		for (int i = index; i < size; i++)
		{
			new(data + i) V(std::move(data[i + 1]));
		}
		size--;

		return Iterator(data + index);
	}
	Iterator find(V& value)
	{

		for (int i = 0; i < size; i++)
		{
			if (data[i] == value)
			{
				return data + i;
			}
		}
		return data + size;
	}
	Iterator begin()
	{
		return Iterator(data);
	}
	Iterator end()
	{
		return Iterator(data + size);
	}
	ConstIterator begin()
	{
		return ConstIterator(data);
	}
	ConstIterator end()
	{
		return ConstIterator(data + size);
	}
	~MyVector()
	{
		clear();
		operator delete(data);
	}
};
