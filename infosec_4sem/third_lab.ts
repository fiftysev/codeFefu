import * as readline from "readline";

class Encoder {
  private rounds: number = 14;

  private ROR(v: string, shift: number): string {
    return v
      .split("")
      .map((v) => {
        return String.fromCharCode(v.charCodeAt(0) >> shift);
      })
      .join("");
  }

  private ROL(v: string, shift: number): string {
    return v
      .split("")
      .map((v) => {
        return String.fromCharCode(v.charCodeAt(0) << shift);
      })
      .join("");
  }

  private V(key: string, i: number) {
    let K1 = key.slice(0, key.length / 2);
    let K2 = key.slice(key.length / 2);

    return this.ROL(K1, i) + this.ROR(K2, i);
  }

  private F(v: string, key: string, i: number) {
    return v
      .split("")
      .map((v, i) => {
        return String.fromCharCode(
          v.charCodeAt(0) ^ key.charCodeAt(i % key.length)
        );
      })
      .join("");
  }

  private XOR(L: string, R: string) {
    return L.split("")
      .map((v, i) => {
        let res = v.charCodeAt(0) ^ R.charCodeAt(i % R.length);
        return String.fromCharCode(res);
      })
      .join("");
  }

  public encode(text: string, key: string) {
    let L: string = text.slice(0, text.length / 2);
    let R: string = text.slice(text.length / 2).padEnd(L.length);

    for (let i = 0; i < this.rounds; i++) {
      let temp: string = L;
      L = R;
      R = this.XOR(temp, this.F(R, this.V(key, i), i));
    }

    return L + R;
  }

  public decode(text: string) {}
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

    console.log(encoder.encode(text, key));

    rl.close();
  });
});
