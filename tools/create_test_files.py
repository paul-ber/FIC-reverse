#!/usr/bin/env python3
import os
import random
import string

def create_test_files():
    """Créer des fichiers de test pour NovaLocker"""
    
    # Créer le dossier de test
    test_dir = r"C:\temp\test_files"
    os.makedirs(test_dir, exist_ok=True)
    
    # Fichiers de test avec contenu "sensible"
    test_files = {
        "project_pulsar_specs.txt": """
CLASSIFIED DOCUMENT - PROJECT PULSAR
=====================================
Quantum Engine Specifications v2.1

Core Parameters:
- Frequency: 2.4 THz
- Power Output: 1.21 GW  
- Efficiency: 97.3%
- Security Classification: TOP SECRET

This document contains sensitive information about the Nova quantum drive project.
FLAG_PART_1: NOVA_192.168.1.25
        """,
        
        "technical_blueprint.doc": """
PROJECT PULSAR - TECHNICAL BLUEPRINT
====================================
Reactor Core Design - Phase 2

Critical Components:
1. Quantum Stabilizer Array
2. Neutron Flux Dampener
3. Emergency Containment System

WARNING: This information is classified under the Nova Corporation security protocols.
FLAG_PART_2: PORT_8080_EXFIL
        """,
        
        "test_results.txt": """
PULSAR PROJECT - TEST RESULTS LOG
=================================
Date: 2025-08-31
Test Series: Alpha-7
Status: CONFIDENTIAL

Results Summary:
- Stability Index: CRITICAL
- Energy Output: 150% of expected
- Risk Assessment: HIGH

Contact Dr. Sarah Chen for detailed analysis.
FLAG_PART_3: COMPLETE_C2_ADDRESS
        """
    }
    
    for filename, content in test_files.items():
        file_path = os.path.join(test_dir, filename)
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(content)
        print(f"Created: {file_path}")
    
    print(f"\nTest files created in: {test_dir}")
    print("Run NovaLocker to encrypt these files")

if __name__ == "__main__":
    create_test_files()
