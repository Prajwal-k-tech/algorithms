# Recovery after a fresh clone

This file records how to restore a working checkout without retaining dependency caches or compiler output.

```bash
git clone --recurse-submodules https://github.com/Prajwal-k-tech/algorithms.git
cd algorithms
```

Start with the committed README for configuration and prerequisites. Git restores committed source and assets. Dependency directories, virtual environments and compiler caches can be rebuilt.


## Data that Git does not restore

A clone restores pushed commits, not unpublished edits, local `.env` files, private keys, trained model weights or local-only data. Preserve such artifacts separately until explicitly replaced, backed up off-device or discarded. Credentials must come from private storage or be regenerated through their provider. No credentials belong in this document.
