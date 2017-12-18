#ifndef SRC_PART_H_
#define SRC_PART_H_

#include <string>

/**
 * Saves all data that concerns one part, assumes that no sale was made, when the unit price is zero
 */
class Part {
private:
	/**
	 * Name of the part
	 */
	std::string name_part;

	/**
	 * Supplier of the part
	 */
	std::string supplier;

	/**
	 * Unit price of the last sale
	 */
	double unit_price;
public:

	/**
	 * Class constructor, assigns all class members its respective values
	 *
	 * @param namePart Name of the part
	 * @param supplier Name of the supplier
	 * @param unitPrice Unit price of the part
	 */
	Part(const std::string& namePart, const std::string& supplier = "",double unitPrice = 0);

	/**
	 * @return Name of the part
	 */
	const std::string& getNamePart() const;

	/**
	 * Sets a new name to the part
	 *
	 * @param namePart Part's new name
	 */
	void setNamePart(const std::string& namePart);

	/**
	 * @return Supplier of the part
	 */
	const std::string& getSupplier() const;

	/**
	 * Changes the supplier of the part
	 *
	 * @param supplier New supplier
	 */
	void setSupplier(const std::string& supplier);

	/**
	 * @return Unit price of the part
	 */
	double getUnitPrice() const;

	/**
	 *	Sets a new unit price for the Part
	 *
	 *	@param unitPrice New unit price for the part
	 */
	void setUnitPrice(double unitPrice);

	/**
	 * Use: to sort Parts in a given container
	 *
	 * @param p1 Part that the object calling the function is to be compared to
	 */
	bool operator<(const Part& p1) const;

	/**
	 * Two part are equal when they have the same name
	 *
	 * @param p1 Part that the object calling the function is to be compared to
	 */
	bool operator==(const Part& p1) const;

	/**
	 *	Prints the Part to a given stream
	 *
	 *	@param out The Part is going to be printed to this stream
	 *	@param p1 Part to print
	 *
	 *	@return Stream given as an argument
	 */
	friend std::ostream& operator<<(std::ostream& out, const Part& p1);
};

#endif /* SRC_PART_H_ */
