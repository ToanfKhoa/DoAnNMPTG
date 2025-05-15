#include "CNumber.h"

void CNumber::Update()
{
	for (int i = 0; i < digitCount; i++)
	{
		int digitValue = (value / (int)pow(10, i)) % 10;
		CDigit* digit = dynamic_cast<CDigit*>(digits[i]);
		if (digit)
		{
			digit->SetValue(digitValue);
		}
	}
}
