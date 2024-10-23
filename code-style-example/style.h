/*! @file MyClass.h */

#ifndef MYPROJECT_MYCLASS_HPP
#define MYPROJECT_MYCLASS_HPP

/**
 * @brief example class
 */
class MyClass {

public:
	/**
	 * @brief example constructor
	 *
	 * @param[integer] t_value example first argument
	 */
	MyClass(int t_value);

	/**
	 * @brief constructor example
	 *
	 */
	MyClass();

	/**
	 * @brief deconstuctor example
	 *
	 */
	~MyClass();

	/**
	 * @brief setter example with correct const implementation
	 *
	 * @param[const integer] t_value first argument
	 */
	void set_value(const int t_value);

	/**
	 * @brief getter example with correct const implementation
	 *
	 * @return const integer
	 */
	const int get_value() const;

	/**
	 * @brief increment member m_value
	 *
	 */
	void increment();

private:
	/**
	 * @m_value basic member example
	 */
	int m_value;
};

#endif
