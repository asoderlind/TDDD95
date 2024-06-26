import time
from collections import defaultdict, Counter


def get_suffix_array(str):
    return sorted(range(len(str)), key=lambda i: str[i:])


def suffix_array_ManberMyers(str):
    result = []

    def sort_bucket(str, bucket, order=1):
        d = defaultdict(list)
        print(d)
        for i in bucket:
            key = str[i : i + order]
            d[key].append(i)
        for k, v in sorted(d.items()):
            if len(v) > 1:
                sort_bucket(str, v, order * 2)
            else:
                result.append(v[0])
        return result

    return sort_bucket(str, (i for i in range(len(str))))


if __name__ == "__main__":
    str = "popup"
    y = suffix_array_ManberMyers(str)
    print(y)
