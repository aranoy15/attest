#include <utils.h>

std::vector<std::string> utils::split(std::string& message, char symbol)
{
	std::vector<std::string> result;
  	std::string temp;	
 
	if (not message.empty()) 
	{
  		for (char item : message)
		{
   			if (item != symbol)
    			temp.push_back(item);
   			else
			{
    			result.push_back(temp);
    			temp.clear();
			}
		}
		result.push_back(temp);
	}
	return result;
}	