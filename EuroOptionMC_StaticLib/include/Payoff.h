#pragma once

namespace payoff
{
	// 'i_payoff' is an abstract base class that defines a standard interface for different payoff calculations.
	class i_payoff
	{
	public:
		virtual ~i_payoff();
		virtual double calculate(double spot_price) const = 0;
	};

	// 'digital_call_payoff' calculates the payoff of a digital call option.
	class digital_call_payoff final : public i_payoff
	{
		double strike_price_; // The strike price of the digital call option.
	public:
		explicit digital_call_payoff(double strike_price);
		// Overrides 'calculate' to compute the digital call option payoff.
		double calculate(double spot_price) const override;
	};

	// 'digital_put_payoff' calculates the payoff of a digital put option.
	class digital_put_payoff final : public i_payoff
	{
		double strike_price_; // The strike price of the digital put option.
	public:
		explicit digital_put_payoff(double strike_price);
		// Overrides 'calculate' to compute the digital put option payoff.
		double calculate(double spot_price) const override;
	};

	// 'european_call_payoff' calculates the payoff of a European-style call option.
	class european_call_payoff final : public i_payoff
	{
		double strike_price_; // The strike price of the European call option.
	public:
		explicit european_call_payoff(double strike_price);
		// Overrides 'calculate' to compute the European call option payoff.
		double calculate(double spot_price) const override;
	};

	// 'european_put_payoff' calculates the payoff of a European-style put option.
	class european_put_payoff final : public i_payoff
	{
		double strike_price_; // The strike price of the European put option.
	public:
		explicit european_put_payoff(double strike_price);
		// Overrides 'calculate' to compute the European put option payoff.
		double calculate(double spot_price) const override;
	};
}
