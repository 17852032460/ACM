
# 2017 杭州CCPC HDU 6265 Master of Phi

> You are given an integer n. Please output the answer of $\sum\nolimits_{d|n}φ(d)×\frac{n}{d}\;modulo\;998244353.$ n is represented in the form of factorization. 
> φ(n) is Euler’s totient function, and it is defined more formally as the number of integers k in the interval 1 ≤ k ≤ n for which the greatest common divisor gcd(n, k) is equal to 1.  
For example, the totatives of n = 9 are the six numbers 1, 2, 4, 5, 7 and 8. They are all co-prime to 9, but the other three numbers in this interval, 3, 6, and 9 are not, because gcd(9, 3) = gcd(9, 6) = 3 and gcd(9, 9) = 9. Therefore, φ(9) = 6. As another example, φ(1) = 1 since for n = 1 the only
integer in the interval from 1 to n is 1 itself, and gcd(1, 1) = 1.
And there are several formulas for computing φ(n), for example, Euler’s product formula states like:  
>$$ \phi(n) = n\prod\nolimits_{p|n}\left(1 - \frac{1}{p}\right), $$
> where the product is all the distinct prime numbers (p in the formula) dividing n.

**Input**
> The first line contains an integer T (1 ≤ T ≤ 20) representing the number of test cases.
For each test case, the first line contains an integer m (1 ≤ m ≤ 20) is the number of prime factors.
The following m lines each contains two integers $p_i$ and $q_i$ (2 ≤ $p_i$ ≤ 108, 1 ≤ $q_i$ ≤ 108) describing that n contains the factor $p_i^{qi}$, in other words, $n=∏^m_{i=1}p_i^{q_i}.$ It is guaranteed that all pi are primenumbers and different from each other.

**Output**

> For each test case, print the the answer modulo 998244353 in one line.
Example

| standard input | standard output |
|:--|:--|
| 2<br>2<br>2 1<br>3 1<br>2<br>2 2<br>3 2 | 15<br>168 |
**Explanation**

For first test case, n = $2^1$ ∗$3^1$ = 6, and the answer is (φ(1)∗n/1+φ(2)∗n/2+φ(3)∗n/3+φ(6)∗n/6) mod 998244353 = (6 + 3 + 4 + 2) mod 998244353 = 15.

**题意**

首先给你一个数m，接着是m对数$p_i$,$q_i$，其中$p_i$为质数，得到一个数 $n = \prod\nolimits^{m}_{i=1}p_i^{q_i}$，然后让你对n的所有因子d求$\sum\phi(d)*\frac{n}{d}$.

**思路**

刚开始看到这道题的时候一脸懵逼，后来恰好学长给我们讲了数论的一些内容，然后更懵逼了。不过还是了解到了一些，比如说这题要用到的狄利克雷卷积。

狄利克雷卷积说的就是说**两个积性函数乘起来还是一个积性函数**。即：h(x) = f(x) * g(x)。  

而积性函数具有的性质是F(x * y) = F(x) * F(y)

然后这题要求解的式子是$\sum\nolimits_{d|n}φ(d) * n/d$，也可以这样写$\sum\nolimits_{d|n}\frac{φ(d)}{d} * n$，而$n= \prod\nolimits^{m}_{i=1}p_i^{q_i}$，这两个都是积性函数，带进去得到$\sum\nolimits_{(d|\prod\nolimits^{m}_{i=1}p_i^{q_i})}\frac{φ(d)}{d} * （\prod\nolimits^{m}_{i=1}p_i^{q_i}）$也就是一个积性函数，利用积性函数的性质就能得到原式=$\prod_{i=1}^m(\sum\nolimits_{d|p_i^{q_i}}\phi(d)*\frac{p_i^{q_i}}{d})$其中$d|p_i^{q_i}$就是$p^0,p^1\cdots p^q$。因此，我们只需要把这m对$p_i$、$q_i$每一对单独求一下题目给的式子，然后把它们累乘起来就好了。剩下的就要推出对于每一对$p_i，q_i$应该怎么求。  

**设$x=p^q$**

$$\sum\nolimits_{d|x}\phi(d)*\frac{x}{d}=\phi(1)*x+\sum\nolimits_{i=1}^q\phi(p^i)*\frac{p^q}{p^i}//将1单独拿出来$$
$$=p^q + \sum\nolimits^q_{i=1}(p-1)p^{i-1}\frac{p^q}{p^i}//欧拉函数展开$$
$$=p^q + (p-1)p^q\sum\nolimits_{i=1}^q \frac{p^{i-1}}{p^i}//常数提出来$$
$$=p^q+(p-1)p^q\sum\nolimits_{i=1}^q\frac{1}{p}//后面就是约分化简$$
$$=p^q + (p-1)\,p^q\,\frac{q}{p}$$
$$=p^q(1+(p-1)\frac{q}{p})$$
$$=p^{q-1}(p+pq-q)$$
  
推到这里答案就显而易见了，只需要把题目中给的所有$p_i$，$q_i$带进去乘起来就好了。
