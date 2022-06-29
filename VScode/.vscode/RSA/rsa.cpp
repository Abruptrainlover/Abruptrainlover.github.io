#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ACCURACY 5
#define SINGLE_MAX 10000
#define EXPONENT_MAX 1000
#define BUF_SIZE 1024

11  /**
 12  * Computes a^b mod c，计算a^b mod c
 13  */
 14 int modpow(long long a, long long b, int c) {
 15     int res = 1;
 16     while(b > 0) {
 17         /* Need long multiplication else this will overflow...
 18          必须使用长乘法，否则这将溢出*/
 19         if(b & 1) {
 20             res = (res * a) % c;
 21         }
 22         b = b >> 1;
 23         a = (a * a) % c; /* Same deal here */
 24     }
 25     return res;
 26 }
 27  
 28 /**
 29  * Computes the Jacobi symbol, (a, n)，计算Jacobi符号（a,n）
 30  */
 31 int jacobi(int a, int n) {
 32     int twos, temp;
 33     int mult = 1;
 34     while(a > 1 && a != n) {
 35         a = a % n;
 36         if(a <= 1 || a == n) break;
 37         twos = 0;
 38         while(a % 2 == 0 && ++twos) a /= 2; /* Factor out multiples of 2 ,减去2的倍数*/
 39         if(twos > 0 && twos % 2 == 1) mult *= (n % 8 == 1 || n % 8 == 7) * 2 - 1;
 40         if(a <= 1 || a == n) break;
 41         if(n % 4 != 1 && a % 4 != 1) mult *= -1; /* Coefficient for flipping，翻转系数 */
 42         temp = a;
 43         a = n;
 44         n = temp;
 45     }
 46     if(a == 0) return 0;
 47     else if(a == 1) return mult;
 48     else return 0; /* a == n => gcd(a, n) != 1 */
 49 }
 50  
 51 /**
 52  * Check whether a is a Euler witness for n，检查a是否为n的欧拉见证 */
 53 int solovayPrime(int a, int n) {
 54     int x = jacobi(a, n);
 55     if(x == -1) x = n - 1;
 56     return x != 0 && modpow(a, (n - 1)/2, n) == x;
 57 }
 58  
 59 /**
 60  * Test if n is probably prime, using accuracy of k (k solovay tests)，用k的精度检查n是否可能是素数 */
 61 int probablePrime(int n, int k) {
 62     if(n == 2) return 1;
 63     else if(n % 2 == 0 || n == 1) return 0;
 64     while(k-- > 0) {
 65         if(!solovayPrime(rand() % (n - 2) + 2, n)) return 0;
 66     }
 67     return 1;
 68 }
 69  
 70 /**
 71  * Find a random (probable) prime between 3 and n - 1在3和（n-1）之间找一个随机素数, this distribution is，
 72  * nowhere near uniform, see prime gaps
 73  */
 74 int randPrime(int n) {
 75     int prime = rand() % n;
 76     n += n % 2; /* n needs to be even so modulo wrapping preserves oddness */
 77     prime += 1 - prime % 2;
 78     while(1) {
 79         if(probablePrime(prime, ACCURACY)) return prime;
 80         prime = (prime + 2) % n;
 81     }
 82 }
 83  
 84 /**
 85  * Compute gcd(a, b)，计算gcd（a,b）
 86  */
 87 int gcd(int a, int b) {
 88     int temp;
 89     while(b != 0) {
 90         temp = b;
 91         b = a % b;
 92         a = temp;
 93     }
 94     return a;
 95 }
 96  
 97 /**
 98  * Find a random exponent x between 3 and n - 1 such that gcd(x, phi) = 1,在3和n-1之间找到随机指数x，使得gcd(x,phi)=1
 99  * this distribution is similarly nowhere near uniform,这种分布同样不接近制服
100  */
101 int randExponent(int phi, int n) {
102     int e = rand() % n;
103     while(1) {
104         if(gcd(e, phi) == 1) return e;
105         e = (e + 1) % n;
106         if(e <= 2) e = 3;
107     }
108 }
109  
110 /**
111  * Compute n^-1 mod m by extended euclidian method，用扩展欧几里得法计算n^-1 mod m
112  */
113 int inverse(int n, int modulus) {
114     int a = n, b = modulus;
115     int x = 0, y = 1, x0 = 1, y0 = 0, q, temp;
116     while(b != 0) {
117         q = a / b;
118         temp = a % b;
119         a = b;
120         b = temp;
121         temp = x; x = x0 - q * x; x0 = temp;
122         temp = y; y = y0 - q * y; y0 = temp;
123     }
124     if(x0 < 0) x0 += modulus;
125     return x0;
126 }
127  
128 /**
129  * Read the file fd into an array of bytes ready for encryption.将文件fd读入准备加密的字节数组
130  * The array will be padded with zeros until it divides the number of数组将填充零，知道它划分每个块加密的字节数
131  * bytes encrypted per block. Returns the number of bytes read.返回读取的字节数
132  */
133 int readFile(FILE* fd, char** buffer, int bytes) {
134     int len = 0, cap = BUF_SIZE, r;
135     char buf[BUF_SIZE];
136     *buffer = (char *)malloc(BUF_SIZE * sizeof(char));
137     while((r = fread(buf, sizeof(char), BUF_SIZE, fd)) > 0) {
138         if(len + r >= cap) {
139             cap *= 2;
140             *buffer = (char *)realloc(*buffer, cap);
141         }
142         memcpy(&(*buffer)[len], buf, r);
143         len += r;
144     }
145     /* Pad the last block with zeros to signal end of cryptogram. An additional block is added if there is no room，将最后一个带有零的块插入密码的信号端。 如果没有房间，则增加一个额外的街区 */
146     if(len + bytes - len % bytes > cap) *buffer = (char *)realloc(*buffer, len + bytes - len % bytes);
147     do {
148         (*buffer)[len] = '\0';
149         len++;
150     }
151     while(len % bytes != 0);
152     return len;
153 }
154  
155 /**
156  * Encode the message m using public exponent and modulus, c = m^e mod n使用公共指数和模量对消息m进行编码，c = m^e Mod n
157  */
158 int encode(int m, int e, int n) {
159     return modpow(m, e, n);
160 }
161  
162 /**
163  * Decode cryptogram c using private exponent and public modulus, m = c^d mod n，用私有指数和公共模量解码密码c，m = c^d Mod n
164  */
165 int decode(int c, int d, int n) {
166     return modpow(c, d, n);
167 }
168  
169 /**
170  * Encode the message of given length, using the public key (exponent, modulus)
171  * The resulting array will be of size len/bytes, each index being the encryption
172  * of "bytes" consecutive characters, given by m = (m1 + m2*128 + m3*128^2 + ..),
173  * encoded = m^exponent mod modulus
174  * 使用公钥（指数、模数)对给定长度的消息进行编码）
175  得到的数组将是大小为len/字节，每个索引是由m=(m1m2*128m3*128^2.)给出的“字节”连续字符的加密，编码=m^指数mod模量
176  */
177 int* encodeMessage(int len, int bytes, char* message, int exponent, int modulus) {
178     int *encoded = (int *)malloc((len/bytes) * sizeof(int));
179     int x, i, j;
180     for(i = 0; i < len; i += bytes) {
181         x = 0;
182         for(j = 0; j < bytes; j++) x += message[i + j] * (1 << (7 * j));
183         encoded[i/bytes] = encode(x, exponent, modulus);
184 #ifndef MEASURE
185         printf("%d ", encoded[i/bytes]);
186 #endif
187     }
188     return encoded;
189 }
190  
191 /**
192  * Decode the cryptogram of given length, using the private key (exponent, modulus)
193  * Each encrypted packet should represent "bytes" characters as per encodeMessage.
194  * The returned message will be of size len * bytes.
195  * 使用私钥（指数、模数)解码给定长度的密码）
196  每个加密的数据包应该按照编码消息表示“字节”字符。
197  返回的消息大小为len*字节。
198  */
199 int* decodeMessage(int len, int bytes, int* cryptogram, int exponent, int modulus) {
200     int *decoded = (int *)malloc(len * bytes * sizeof(int));
201     int x, i, j;
202     for(i = 0; i < len; i++) {
203         x = decode(cryptogram[i], exponent, modulus);
204         for(j = 0; j < bytes; j++) {
205             decoded[i*bytes + j] = (x >> (7 * j)) % 128;
206 #ifndef MEASURE
207             if(decoded[i*bytes + j] != '\0') printf("%c", decoded[i*bytes + j]);
208 #endif
209         }
210     }
211     return decoded;
212 }
213  
214 /**
215  * Main method to demostrate the system. Sets up primes p, q, and proceeds to encode and
216  * decode the message given in "text.txt"
217  * 系统降级的主要方法。 设置素数p，q，并开始编码和
218  *解码“text.txt”中给出的消息；
219  */
220 int main(void) {
221     int p, q, n, phi, e, d, bytes, len;
222     int *encoded, *decoded;
223     char *buffer;
224     FILE *f;
225     srand(time(NULL));
226     while(1) {
227         p = randPrime(SINGLE_MAX);
228         printf("生成第一个随机素数, p = %d ... ", p);
229         getchar();
230  
231         q = randPrime(SINGLE_MAX);
232         printf("生成第二个随机素数, q = %d ... ", q);
233         getchar();
234  
235         n = p * q;
236         printf("计算p和q的乘积n, n = pq = %d ... ", n);
237         if(n < 128) {
238             printf("Modulus is less than 128, cannot encode single bytes. Trying again ... ");
239             getchar();
        }
        else break;
    }
    if(n >> 21) bytes = 3;
    else if(n >> 14) bytes = 2;
    else bytes = 1;
    getchar();
 
    phi = (p - 1) * (q - 1);
    printf("计算欧拉函数的值phi, phi = %d ... ", phi);
    getchar();
 
    e = randExponent(phi, EXPONENT_MAX);
    printf("选取一个随机素数e, e = %d...\n获得公钥 (%d, %d) ... ", e, e, n);
    getchar();
 
    d = inverse(e, phi);
     printf("计算模反元素d, d = %d...\n获得密钥 (%d, %d) ... ", d, d, n);
    getchar();
 
    printf("打开文件 \"text.txt\" 用于读取信息\n");
    f = fopen("text.txt", "r");
    if(f == NULL) {
        printf("Failed to open file \"text.txt\". Does it exist?\n");
        return EXIT_FAILURE;
    }
    len = readFile(f, &buffer, bytes); /* len will be a multiple of bytes, to send whole chunks伦将是多个字节，以发送整个块 */
    fclose(f);
    printf("文件 \"text.txt\" 读取成功, 读取到%d字节. 以%d字节的字节流编码 ... ", len, bytes);
    getchar();
    printf("加密得密文为：");
     encoded = encodeMessage(len, bytes, buffer, e, n);
   printf("\n编码成功完成 ... ");
   getchar();
 
    printf("正在解码编码的信息 ... ");
    getchar();
   printf("解码得明文为：");
   decoded = decodeMessage(len/bytes, bytes, encoded, d, n);


    printf("\nRSA算法演示完成!\n");
 
    free(encoded);
    free(decoded);
    free(buffer);
    return EXIT_SUCCESS;
}