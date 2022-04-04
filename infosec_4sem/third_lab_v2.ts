import * as readline from "readline";

class Encoder {
  private rounds: number = 14;

  private ROR(v: string, shift: number): number[] {
    return v.split("").map((v) => {
      return v.charCodeAt(0) >> shift;
    });
  }

  private ROL(v: string, shift: number): number[] {
    return v.split("").map((v) => {
      return v.charCodeAt(0) << shift;
    });
  }

  private V(key: string, i: number) {
    let K1 = key.slice(0, key.length / 2);
    let K2 = key.slice(key.length / 2);

    return this.ROR(K1, i).concat(this.ROL(K2, i));
  }

  private F(v: number[], key: number[], n: number) {
    return v.map((v, i) => {
      return (v * key[i % key.length]) % 2 ** n;
    });
  }

  private XOR(L: number[], R: number[]) {
    return L.map((v, i) => {
      return v ^ R[i];
    });
  }

  private getBlocks(text: string): [number[], number[]] {
    if (text.length % 2 !== 0) {
      text = text.padEnd(text.length + 1);
    }

    let plainBlock = text.split("").map((v) => v.charCodeAt(0));

    let L: number[] = plainBlock.slice(0, plainBlock.length / 2);
    let R: number[] = plainBlock.slice(plainBlock.length / 2);

    return [L, R];
  }

  public encode(text: string, key: string) {
    let [L, R] = this.getBlocks(text);

    for (let i = 1; i < this.rounds + 1; i++) {
      let temp: number[] = L;
      L = R;
      R = this.XOR(temp, this.F(R, this.V(key, i), i));
    }

    let encoded = L.concat(R);

    return encoded.map((v) => String.fromCharCode(v)).join("");
  }

  public decode(text: string, key: string) {
    let [L, R] = this.getBlocks(text);

    for (let i = 1; i < this.rounds + 1; i++) {
      let temp: number[] = L;
      L = R;
      R = this.XOR(
        temp,
        this.F(R, this.V(key, this.rounds - i), this.rounds - i)
      );
    }

    let decoded = L.concat(R);

    return decoded.map((v) => String.fromCharCode(v)).join("");
  }
}

let rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

let text: string = "";
let key: string = "";

let encoder = new Encoder();

rl.question("Enter text to encode: ", (v) => {
  let test: string = "test";
  text = v;

  rl.question("Enter key: ", (v) => {
    key = v;

    let encoded = encoder.encode(text, key);

    console.log("--------------------------");
    console.log(`Encoded: ${encoded}`);
    console.log("--------------------------");

    console.log("--------------------------");
    console.log(`Decoded: ${encoder.decode(encoded, key)}`);
    console.log("--------------------------");

    rl.close();
  });
});
