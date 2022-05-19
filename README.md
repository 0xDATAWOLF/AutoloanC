# AutoloanC - An Automobile Loan Calculator

A somewhat simple auto loan calculator built to be ran on the command line. It can be configured
to calculate a loan based the vehicle MSRP, trade-in value, down payment, APR, and term length.
This program is designed to be quick and easy, but also allows for data to be exported and/or
tabuluted for a range of term lengths beyond the requested.

## Calculator Definitions & Guide

This calculator assumes a variety of defaults that may not apply to your situation. Use `autoloanc -p`
to use prompt-mode for all the necessary prompts to accurately calculate your loan amount. Optionally,
you can pass in your financial parameters as arguments using the proper commands listed in the table
below. Since APR varies on term length, you will need to acquire APR and term rates from your lender.

> It is *recommended* to pre-determine your purchase price before using this calculator.

Below is a table of definitions for various terms used in the calculator:

* **Vehicle Price**

	The vehicle price is the total cost of the vehicle before taxes and trade-in.

* **Trade-in**

	The trade-in value is how much the vehicle you are trading in is worth. This is determined by what the
	dealer is offering you or the current market value. Sources like KBB and NADA will provide market rates.

* **Trade-in Payoff**

	If the vehicle you're trading in is financed, this value can be used to determined how much money is owed
	to you or the lender after subtracting it from the trade-in value. You can acquire this information from
	your lender. A 10-day payoff quote is typically what is used to determine your payoff amount.

* **Taxes**

	Vehicle sales tax are applied at the time of purchase. This value is determined by your state, county,
	city, and municipality. You can find this information freely available on the internet or by asking your 
	lender or dealer what the tax percentages are in your area.

* **Dealer Fees, Title & Registration**

	Dealer fees, title, and registration may apply differently depending on your state. The combined total
	of dealer fees (or documentary fees), title, and registration aren't a signficant cost, but their 
	application to taxes varys state by state. The application of these fees are included after tax, but
	may not representative of the actual cost of the vehicle. Dealer fees, in particular, are difficult to
	judge and vary wildly between dealership to dealership. Some dealerships publish their documentary fees
	on their website, others you may need to contact.

* **Purchase Price**

	The purchase price of the vehicle is the amount owed after trade-in and tax. Some states calculate tax
	after trade-in, while others do not. It is recommended that you determine this value before using this
	calculator, as the purchase price of your vehicle is heavily influenced by your location. In addition
	to that, how that tax applies varies by your state. Some states may apply taxes after down payment and
	trade-in, or only after trade-in, or before trade-in and down payment. Purchase price also includes any
	additional dealer fees, tile, and registration that is occured at the time of purchase.

* **Term Length**

	The term length of your loan is the number of months until loan pay-off.

* **APR**

	The APR, or annual percentage rate, is what determines how much you will pay to finance your vehicle with
	your lender. The value of your APR is dependent on your credit and the term length of the loan. This
	information will be given to you by your lender for any given term length.

* **Loan Balance**

	The loan balance is the total amount financed with your lender. APR is factored into this.

* **Interest Paid**

	Interest paid is the difference of purchase price and loan balance.

* **Monthly Payment**

	The amount paid per month for the term length of the loan.


## Useage & Commands

The calculator can be invoked by running it in two modes, argument-mode and prompt-mode. Argument-mode
is implicit, meaning that the calculator expects arguments to be passed to it. To invoke prompt-mode,
simply use `autoloanc -p` or `autoloanc --prompt`. For general useage, pass in the loan amount and the
calculator will use the default finance parameters (APR and term length). 

<table width="100%">
	<thead>
		<th>Command</th>
		<th>Useage</th>
	</thead>
	<tbody>
		<tr>
			<td>-h,--help</td>
			<td>Displays the help dialogue.</td>
		</tr>
		<tr>
			<td>-p,--prompt</td>
			<td>
				Invokes the calculator's prompt-mode. This mode will prompt for all financial parameters.
				Required parameters are denoted with asterisk. Additional parameters are ignored.
			</td>
		</tr>
	</tbody>
</table>
