[分布式之redis复习精讲](https://www.cnblogs.com/rjzheng/p/9096228.html)
[值得一看的35个Redis常用问题总结](https://www.cnblogs.com/huyong/p/9961906.html)

## Redis特点&数据结构&自身实现
1. 为什么在业务里用 Redis, Redis 有什么优点
    - 单线程：并发安全；高性能；
    - 原语与数据结构丰富，支持string，list，hash，set，sorted set
    - 丰富的特性：订阅/发布，key过期策略，事务，计数
    - 持久化存储
    - 采用广泛，踩坑成本低
2. Redis里有哪些数据结构体
    - 简单动态字符串SDS
    - 链表
    - 字典（双hash表dictht, rehash）
        ![](https://raw.githubusercontent.com/roperluo32/images/master/image20191201120755.png)
        
        ![](https://raw.githubusercontent.com/roperluo32/images/master/image20191201120816.png)
    - 跳跃表（平衡查找树的简化版）
    - 整数集合（升级和降级）
       - ![](https://raw.githubusercontent.com/roperluo32/images/master/image20191201194418.png)
    - 压缩列表
       - ![](https://raw.githubusercontent.com/roperluo32/images/master/image20191201194531.png)
    
3. 用过Redis的哪些对象
    - 有5种对象：字符串，列表，哈希表，集合，有序集合
    ![](https://raw.githubusercontent.com/roperluo32/images/master/image20191201194715.png)
    - 每种对象基本都有两种对应的底层实现方式
    ![](https://raw.githubusercontent.com/roperluo32/images/master/image20191201195016.png)
4. Redis各个对象的使用场景
    - 链表：异步队列；秒杀商品队列
    - 哈希：保存结构体
    - 集合：利用它的唯一性，用在一些去重的场景
    - 有序集合：用来保存排行榜，有序列表等等
15. zrange start, stop, 总长度为 n, 复杂度是多少
    - log(n)+m, 先用log(n)的时间找到元素起点，然后遍历最底层链表，找到stop，要查找的个数即为m

26. redis的hash算法用的是啥
    - redis应该是使用一致性hash算法—MurmurHash3 算法，具有低碰撞率优点，google改进的版本cityhash也是redis中用到的哈希算法。现有的主流的大数据系统都是用的 MurmurHash本身或者改进"
42. redis队列应用场景
    - 实现消息队列
    - 秒杀商品池
44. redis用的哪个版本
    - 使用info命令查看版本
    - redis3.0（里程碑），开始支持redis cluster集群功能
    - redis4.0，redis cluster支持NAT和docker
    - redis5.0，支持新的数据类型stream，用于实现消息队列。[基于Redis的Stream类型的完美消息队列解决方案](https://zhuanlan.zhihu.com/p/60501638)
48. Redis说一下sorted set底层原理
    - zset是使用skiplist+dict以及ziplist两种方案实现的
    - 当集合个数比较少（128个）且元素长度较短（64位）时，就会用压缩列表ziplist来实现
    - 否则就会用skiplist+dict来实现。其中dict用来在o(1)时间内找到元素。而skiplist用来做范围查找
49. sorted set实现为什么要用skiplist，而不用平衡树
    - skiplist的维护比较简单，只需要修改前后指针就能实现，复杂度o(1)。而平衡树需要一系列旋转操作,复杂度o(n)
    - 执行zrange的效率高，skiplist第一层是一个有序链表，可以高效地执行range范围操作
    - 通过调整概率参数可以平衡内存和效率

57. redis常见性能问题和解决方案
    - master上最好不要做任何持久化操作，包括内存快照和AOF。如果数据比较重要，就在slave上开启AOF
    - 主从机器最好在同一局域网，保证网络稳定性。另外不要在压力比较大的master上增加slave，会导致master挂掉
    - 使用链式的结构。master <- slave <- slave ...这样可以减轻master的压力
58. redis与memcache优缺点对比
    - redis：支持丰富的数据类型（string，list，hash，set，sortedset），值最大1G，支持发布/订阅，脚本等丰富的机制。支持事务，支持数据备份&持久化
    - memcache：只支持字符串，值最大1M，只适合存储静态字符串数据
    - 一般建议使用redis，只有在系统需要兼容旧模块使用的memcache时才考虑

59. redis常用命令
    - 管理命令
       -  查看Redis的相关信息：info
       -  清空当前database的键值对：flushdb
       -  清空全部database的键值对：flushall
       -  查看当前database中键值对的数量：dbsize
       -  手动触发的Redis持久化操作：save
    - 键命令
       - set, mset, setnx，get, getset 
       - del, exists, ttl, 
       - 设置已经存在的<key>的过期时间：expire
       - 设置新<key>的过期时间：setex, psetex（毫秒）
       - type，random，rename
    - 字符串
       - strlen， append， incr/decr, incrby/decrby
    - hash
       - hset/hmset, hdel, hget/hmget, hgetall, hkeys, hvals, hlen
    - list
       - lpush, lpop, lset, llen, lindex, lrange(获取指定index范围内的元素)
    - set
       - sadd， srem, smembers, scrad, sismember, spop, rename
       - sdiff, sinter, sunion(计算两个集合的交并集，差集)
    - zset
       - zdd， zrem，zcard
       - 获取zset中元素分数。zscore
       - 获取zset某个分数区间的元素个数。zcount 
       - 获取zset的某个元素的索引。zrank
       - 加减zset的某个元素的score。zincrby
       - 通过索引区间返回有序集合指定区间内的成员。zrange
       - 通过分数返回有序集合指定区间内的成员。zrangebyscore
    - [Redis 常用命令整理](https://www.jianshu.com/p/cca973a6c55d)
## 同步
1. redis 同步机制
    - 旧版复制(2.8版本以前)。分为同步（sync）和命令传播（command propagate），同步是主给从传送rdb文件，命令传播是主将对数据库有更新的命令发给从执行。缺陷：断线重连需要重复同步（sync）步骤，传送rdb文件非常耗资源
    - 新版复制。PSYNC命令。主保存了一个复制积压缓冲区（replication backlog），同时主从都有一个复制偏移量(replication offset)，用来指示当前复制到哪里了。断线重连后不需要重复整个sync过程，只需要通过偏移量来增量复制就行了
    
    ![](https://raw.githubusercontent.com/roperluo32/images/master/image20191203071858.png)

## 缓存
1. 缓存机器增删如何对系统影响最小
    - 一致性哈希。普通的一致性hash有数据倾斜的问题，增加了虚拟节点来避免这个问题。所谓虚拟节点，即是把物理节点虚拟出N个节点分布到hash环上，以达到均匀获取数据的目的。
    - hash slot。redis cluster的实现就使用了hash slot方法来分配数据
19. Redis的缓存过期检查策略	
    - 惰性删除 + 定期清理（每次只检查M个数据库和N条expires里面的记录，防止阻塞太久）
24. redis的数据淘汰策略	
    - volatile-lru：从已设置过期时间的数据集（server.db[i].expires）中挑选最近最少使用 的数据淘汰
    - volatile-ttl：从已设置过期时间的数据集（server.db[i].expires）中挑选将要过期的数 据淘汰
    - volatile-random：从已设置过期时间的数据集（server.db[i].expires）中任意选择数据 淘汰
    - allkeys-lru：从数据集（server.db[i].dict）中挑选最近最少使用的数据淘汰
    - allkeys-random：从数据集（server.db[i].dict）中任意选择数据淘汰
    - no-enviction（驱逐）：禁止驱逐数据
    - [Redis 数据淘汰机制](https://wiki.jikexueyuan.com/project/redis/data-elimination-mechanism.html)
20. Redis缓存失效逻辑为什么只有master才能操作？
    - 为了保持redis设计的简单。从redis不允许直接删除键，只允许从主那里同步删除键
20. 缓存穿透的解决办法
    - 缓存穿透：大并发访问不存在的key，导致大量的底层存储访问
    - 解决办法：1. 保存空值（设置过期时间） 2. 利用布隆过滤器，来判断key是否存在
21. 缓存雪崩
    - 含义：同一时间大批量的key同时过期
    - 解决：1. 给key的过期时间设置一定的随机量，避免同时过期 2. 通过锁或者队列去控制读取底层存储的并发量
22. 热点key失效导致的缓存击穿
    - 含义：某个热点key失效，会导致大量的底层存储访问
    - 解决： 1. 给key加锁，同一时间只允许一个线程去访问底层存储 2. 给key加上随机数，使访问均匀分布到多台机器上。访问的时候也需要使用热点key+随机数
    - [Redis缓存雪崩、缓存穿透、热点Key解决方案和分析](https://blog.csdn.net/wang0112233/article/details/79558612)
56. 如何保证redis和数据库数据的一致性。比如用户名既保存在数据库，又保存在redis做缓存。有如下操作 update_db(username); update_redis(username)。但是执行update_db后故障，update_redis没有执行。有什么简单办法解决这个问题。	
    - 先淘汰缓存，再淘汰数据库
    - [
redis缓存与数据库一致性问题解决](https://blog.csdn.net/qq_27384769/article/details/79499373)
22. mySQL里有2000w数据，redis中只存20w的数据，如何保证redis中的数据都是热点数据
    - redis的六种内存数据淘汰机制
        - 优先淘汰已设置过期时间的键中最少被使用的LRU
        - 优先淘汰已设置过期时间键中剩余时间最短的TTL
        - 随机淘汰已设置过期时间的键
        - 优先淘汰所有键空间中最少被使用的LRU
        - 随机淘汰键空间中的键
    - redis过期检测策略
        - 惰性检查
        - 定期批量检查
23. 用Redis和任意语言实现一段恶意登录保护的代码，限制1小时内每用户Id最多只能登录5次	
```
// 函数省略了错误处理
func login(user string) bool {
  count, err = redis.Int(redis.c.Do("llen", user))
  lastlogin, err = redis.Int(redis.c.Do("lindex", user, "0"))

  now = time.Now().Unix()
  // 一小时内登陆超过5次
  if now - lastlogin < 3600 && count >= 5 {
    return false
  }

  if count >= 5 {
     redis.c.Do("lpop", user)
  }
  redis.c.Do("rpush", user, now)
}
```


## 持久化
1. Redis持久化的几种方式，优缺点是什么，怎么实现的	
    - RDB快照和AOF两种方式
    - RDB，优点：内容紧凑，文件体积比较小，恢复速度快且不容易出错。缺点：备份成本高，无法做到实时备份，机器故障时数据丢失多
    - AOF：优点：实时备份，备份成本低。可以设置每秒fsync一次，机器故障最多丢失1秒的数据。可以通过AOF重写减小体积。 缺点：文件体积偏大，恢复时出错可能性较大
35. Redis的持久化？有哪些方式，原理是什么？	
     - RDB。对redis中所有数据的一个快照，使用紧凑的二进制存储
     - AOF。以append追加日志的形式记录更新redis数据的命令，使用文本形式存储。redis会定时通过AOF重写来减小AOF文件的大小。
51. redis 的持久化是否能够信任
    - redis提供了aof everysec的选项，可以保证最多2s的数据丢失。对比mysql的持久化，可信任级别已经算比较高了。
    - [Redis 持久化深入--机制、可靠性及比较](https://www.cnblogs.com/luojiahu/p/9624392.html)
60. AOF如何缩减自身文件大小
    - 通过对现有redis数据库的状态生成写入命令，从而将历史命令合并为一条命令
61. AOF缩减自身文件大小的时候，数据库来了新的操作怎么办	       
    - AOF重写过程会有一个AOF重写缓冲区，新的操作会写入缓冲区。等重写过程结束后，会读取缓冲区的命令写入AOF文件


## Redis重要应用 分布式锁&全局ID生成器
##### 一，redis锁    
1. 单机锁  
   - set key my-random-value   NX PX millsecond
   - 问题：1. 抢锁问题。没有释放锁的情况下，被其它进程抢锁。 2. failover问题。redis机器挂掉重启，备份不及时导致锁丢失
   - 解决办法：1.资源端校验请求的随机数（资源端需要做修改，不推荐）  2. 请求端检查锁的随机数（但还是无法解决问题，比如检查ok后发生GC）

2. 分布式锁 redlock
   - 流程：使用5台master redis  
   - 1. 向5台redis请求锁 
   - 2. 每台redis最多等待N秒，N为锁时间的1/10  
   - 3. 如果获取到半数以上redis的锁，并且获取锁的总时间小于锁时间，那么就得到了锁  
   - 4. 如果锁成功了，那么使用锁的时间为锁时间减去获取锁的时间  
   - 5. 如果获取锁失败了，那么要给所有redis都发送释放锁的请求，不管之前有没有获取成功
   - 问题：1. 解决了redis机器挂掉重启的问题，2. 没有解决抢锁的问题 3.依赖系统时钟，如果某台机器发生大的时钟跳跃，会导致锁提前释放（以为redis的expire是使用pexpireat实现的）

 ##### 二，zookeeper锁
- zookeeper依靠session机制（定时心跳）来判断锁的持有状态，因此不需要像redis一样设置锁的过期时间。
- zookeeper有watch机制，客户端可以更好地模拟锁（阻塞），而不需要去轮询。
- 问题：
    - 1. 惊群效应。当进程释放锁后，其它等待锁的进程会被同时唤醒，导致锁的效率低下。解决方案：使用有序临时节点，只有持有最低序号的节点持有锁，其它节点watch它前面的一个节点
    - 2. 抢锁。zookeeper还是会有抢锁问题，当zk长时间收不到心跳，就会把进程的锁释放掉，这时候进程的锁就会被其它进程抢走。

**总结**：
1. 如果业务不要求强一致的锁（比如锁只是用来限制不要重复请求），那么用单机版的redis锁就够用了
2. redlock解决了单机redis锁的failover问题，但是没有解决抢锁问题
3. zookeeper提供了一些分布式上的便利，利用心跳来判断锁的有效性，利用watch来阻塞锁，同时本身也是解决了failover问题的。但是根本上还是没有解决抢锁的问题

[分布式锁的一点理解](https://www.cnblogs.com/suolu/p/6588902.html)

[基于Redis的分布式锁真的安全吗？（上）](http://zhangtielei.com/posts/blog-redlock-reasoning.html)

[基于Redis的分布式锁到底安全吗？（下）](http://zhangtielei.com/posts/blog-redlock-reasoning-part2.html)

1. 我现在要做一个限流功能, 怎么做
    - 令牌桶
    - [15行Python代码，帮你理解令牌桶算法](https://juejin.im/post/5ab10045518825557005db65)
    - [分布式服务限流实战，已经为你排好坑了](https://www.infoq.cn/article/Qg2tX8fyw5Vt-f3HH673)
5. 这个限流要做成分布式的, 怎么做
    - 令牌桶维护到 Redis 里，每个实例起一个线程抢锁，抢到锁的负责定时放令牌
    - [基于Redis的限流系统的设计](https://www.jianshu.com/p/a3d068f2586d)
6. 怎么抢锁	
    - Redis setnx
7. 锁怎么释放
    - 抢到锁后设置过期时间，线程本身退出时主动释放锁
    - 假如线程卡住了，锁过期那么其它线程可以继续抢占
9. 加了超时之后有没有可能在没有释放的情况下, 被人抢走锁	    
    - 有可能，单次处理时间过长，锁泄露
10. 怎么解决?	
    - 换zk，用心跳解决。
    - **评语：其实用zk的心跳也没法避免抢锁的问题。能解决抢锁的一个办法是在资源端做锁的版本检查(fencing机制)**
11. 不用zk的心跳, 可以怎么解决这个问题呢
    - 每次更新过期时间时，Redis 用 MULTI 做 check-and-set
    - 检查更新时间是否被其他线程修改了，假如被修改了，说明锁已经被抢走，放弃这把锁
    - **评语：客户端做CAS也无法解决抢锁的问题，客户端检查ok后如果发生长时间的GC，锁同样也会被其它进程抢走**
12. 分布式锁需要具备哪些条件
    - 互斥性：在任意一个时刻，只有一个客户端持有锁。
    - 无死锁：即便持有锁的客户端崩溃或者其他意外事件，锁仍然可以被获取。
    - 容错：不会因为某台机器挂掉就导致锁机制失效。只要大部分Redis节点都活着，客户端就可以获取和释放锁
    - [redis系列：分布式锁](https://juejin.im/post/5b737b9b518825613d3894f4)
13. 分布式锁的实现有哪些？
    - 数据库
    - Memcached（add命令）
    - Redis（setnx命令）
    - Zookeeper（临时节点）

14. 分布式ID的特性
    - 唯一性：确保生成的ID是全网唯一的。
    - 有序递增性：确保生成的ID是对于某个用户或者业务是按一定的数字有序递增的。
    - 高可用性：确保任何时候都能正确的生成ID。
    - 带时间：ID里面包含时间，一眼扫过去就知道哪天的交易。
    
14. 某一个业务中现在需要生成全局唯一的递增 ID, 并发量非常大, 怎么做
    - 利用msyql的自增ID。缺点：单机性能差，每次请求都要读写数据
    - mysql自增ID改进方案：使用多台mysql，不同mysql使用不同步长增长。同时使用批量发号，解决每次请求都读写的问题。缺点：发号不够随机，容易被猜出发号信息；db宕机导致整个集群不可用；业务端号码用完时会出现请求db毛刺（可以使用双buffer，号码快用完时提前请求）[Leaf——美团点评分布式ID生成系统](https://tech.meituan.com/2017/04/21/mt-leaf.html)
    - UUID. 缺点：长度过长，36个字符不适合直接用来当主键；完全随机的，不是递增
    - Redis生成自增ID。有单点风险。改进：使用多台redis，配置以不同步长递增。缺点：业务需要额外部署redis，增加部署成本。
    - snowflake算法。优点：不依赖db，效率高，递增有序。缺点：严重依赖本机时钟，如果时钟回拨会导致重复生成ID。解决办法：引进zk，启动时配置workerID和时钟
    - 
    [分布式唯一ID的几种生成方案](https://juejin.im/post/5b3a23746fb9a024e15cad79)


## Redis 高并发&集群

16. Redis的并发竞争问题如何解决
    - 主要是并发写的会出问题。
    - 1.使用原子的incr命令去写
    - 2.使用watch机制，如果watch的变量有改动，事务就不会执行
    - 3.使用分布式锁，例如setnx或者zookeeper
    - 4.使用消息队列，将并发读写转成串行
    - [Redis的并发竞争问题](https://www.cnblogs.com/shamo89/p/8385390.html)
17. 了解Redis事务的CAS操作吗
     - 通过watch指定变量，如果执行事务时该变量有变化，就停止执行事务
21. redis集群，高可用，原理	
     - redis集群。通过将16384个槽指派给不同的节点来实现集群。
     - 高可用。通过为每个主节点指定从节点，从节点复制主节点的数据。当检测到主节点有故障时，就会自动用从节点去替换主节点。
25. redis/zk节点宕机如何处理
     - 分情况处理：主节点/从节点，有持久化/没有持久化
     - 从节点&持久化，那么重启从节点，并读取持久化，从节点会自动增量同步主节点达到一致
      - 从节点&非持久化。由于需要全量同步，不要在业务量很大的情况下执行全量同步，否则会导致主节点处理业务缓慢，找一个业务低峰期去做同步
     - 主节点&持久化。这里也要分情况去处理：主节点宕机了多久。对于刚宕机的主节点，且没有其他从节点代替其主节点，此时直接启动主节点即可。如果已经宕机很久，且有其他从节点已经代替其成为主节点，那么就将其设置为从节点重启
     - 主节点&非持久化。此时就将从节点设置为主节点，并且根据此时业务负载情况去重启宕机节点。
   
31. 如何解决高并发减库存问题
     - 利用watch机制，保持减库存事务的原子性和隔离性
     - 利用setnx key unique-value PX millsecond NX 实现锁。但该锁无法避免抢锁问题
     - 使用incr和incrby去作原子写
37. Redis使用哨兵部署会有什么问题
    - 切换从节点后，客户端无法自动切换写节点（还会往之前的master节点上写）
    - 写集中在单节点上，无法突破单机写瓶颈
    - 扩容的话还是得集群部署	
38. redis集群的理解，怎么动态增加或者删除一个节点，而保证数据不丢失。（一致性哈希问题）
    - redis集群将数据分为了16384个槽，增加节点时，会使用redis-trib工具从其他节点上分配一些槽到新节点上
    - 删除节点时，会先把该节点上的槽先转移到其它节点
39. Redis的并发竞争问题如何解决
     - 使用set key unique-value PX millsecond NX来实现简单的锁
     - 使用watch，multi，exec命令，来实现事务性操作
     - 使用incr，incrby原子命令去执行一些简单的操作
40. 了解Redis事务的CAS操作吗
     - watch机制，执行事务前会先检查watch是否有变化，如果有变化就不再执行事务
45. 如何搭建redis集群
     - CLUSTER MEET 127.0.0.1 7001  //执行该命令来加入到集群
     - CLUSTER NODES   //查看集群中的机器
     - CLUSTER ADDSLOTS 5001 5002 ... 10000  //指派槽节点
     - CLUSTER KEYSLOT "fruit"         //查看一个key属于哪个槽
46. redis如何主从同步
     - 通过复制偏移量，复制积压缓冲区，主服务器ID来实现部分重同步
     - 主服务器通过向从服务器发送更新命令保持同步，从服务器通过定时向主服务器发送心跳来进行命令丢失检测
47. redis分布式锁注意事项
     - set key unique-value PX millsecond NX
     - 无法解决抢锁的问题
     - 锁的释放有两条命令，get和del，因此需要用事务或者lua脚本来保证原子性
     - 只释放自己的锁
     - 锁设置过期时间，避免获取锁的进程挂掉导致死锁
52. 假如一个业务依赖单点redis，此redis故障将导致业务不可用，如何改进	
     - 最简单的是使用主从redis，主redis故障后自动切换从redis。同时可以使用哨兵来做自动主从切换（但是客户端还是得自动切换写机器）
     - 更好的方案是使用集群redis
54. 当大量数据要求用redis保存，单机单点难以满足需要，设计（换寻找）一个负载均衡的方案
     - 使用redis集群模式，将key映射到16384个槽上。集群中多个redis节点根据处理能力分配相应数量的槽
55. 当redis 采用hash做sharding，现在有8个节点，负载方案是 pos = hash(key) % 8，然后保存在pos节点上。这样做有什么好处坏处？当8个节点要扩充到10个节点，应该怎么办？有什么更方便扩充的方案吗？（一致性hash, presharding）
     - 好处是运算简单，坏处是扩缩容时，会导致大量数据迁移
     - 更加方便的是使用一致性hash，或者类似redis集群的预分配槽
58. redis集群如何保证一致性？
     - 通过主从同步来保证数据最终一致性
     - 使用复制偏移量，复制积压缓冲区，服务器ID来实现异步同步
     - 主给从发送更新命令来保持同步，从定期给主发送心跳，来进行命令丢失检测
50. 考虑redis的时候，有没有考虑容量？大概数据量会有多少	
     - redis数据量由单位时间内请求的key数量与key的保存时间来决定
     - 会利用redis容量预估工具估算一个大概的内存使用量
     - [Redis容量预估](http://www.redis.cn/redis_memory/)
53. redis集群的实现方案
    - 客户端sharding。客户端自己维护key的映射关系。实现简单，运维和故障迁移比较麻烦
    - 中间件的方式。Twemproxy和Codis。优点是对客户端来说 是透明的，使用简单。缺点是部署组件多
    - 官方的redis cluster方案。升级成本高，需要同时升级客户端和服务端
    - [Redis集群的方案总结：客户端Sharding/Redis Cluster/Proxy](https://blog.csdn.net/KingCat666/article/details/78552511)

	
## 其它问题
27. nosql为啥比sql快	 
   - Nosql是非关系型数据库，因为不需要满足关系数据库数据一致性等复杂特性所以速度快；
   - sql是关系型数据库，功能强大，但是效率上有瓶颈
29. 什么是索引？为啥nosql没索引？
    - nosql有索引滴
    - MongoDB会自动在所有集合的_id属性上建立索引


## redis的使用
1. 假如Redis里面有1亿个key，其中有10w个key是以某个固定的已知的前缀开头的，如果将它们全部找出来？
    - 使用keys指令可以扫出指定模式的key列表。
    - 对方接着追问：如果这个redis正在给线上的业务提供服务，那使用keys指令会有什么问题？
    - 这个时候你要回答redis关键的一个特性：redis的单线程的。keys指令会导致线程阻塞一段时间，线上服务会停顿，直到指令执行完毕，服务才能恢复。这个时候可以使用scan指令，scan指令可以无阻塞的提取出指定模式的key列表，但是会有一定的重复概率，在客户端做一次去重就可以了，但是整体所花费的时间会比直接用keys指令长
    - [Redis 中 Keys 与 Scan 的使用](https://learnku.com/articles/25892)

	
	
	



	


	

	

	
	

	



	
	



	

